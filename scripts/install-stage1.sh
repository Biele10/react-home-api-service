#!/usr/bin/env bash

# ==========================================
# Samaritan - Stage 1 Environment Installer
# ==========================================

set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

success() {
    echo -e "${GREEN}[ OK ]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

die() {
    echo -e "${RED}[FAIL]${NC} $1" >&2
    exit 1
}

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# ==========================================
# Check Linux
# ==========================================

info "Checking operating system..."

[[ "$(uname -s)" == "Linux" ]] ||
    die "This installer must be run on Linux."

success "Linux detected."

# ==========================================
# Check root
# ==========================================

info "Checking root privileges..."

[[ "${EUID}" -eq 0 ]] ||
    die "Please run this script with sudo."

success "Running as root."

# ==========================================
# Detect distribution
# ==========================================

if [[ -f /etc/os-release ]]; then
    # shellcheck disable=SC1091
    source /etc/os-release
else
    die "Cannot determine Linux distribution."
fi

info "Detected: ${PRETTY_NAME:-unknown Linux distribution}"

# ==========================================
# Check deployment user
# ==========================================

info "Checking for ubuntu user..."

if id ubuntu >/dev/null 2>&1; then
    success "User 'ubuntu' found."
else
    die "User 'ubuntu' does not exist."
fi

# ==========================================
# Update apt
# ==========================================

info "Updating package lists..."

apt-get update

success "Package lists updated."

# ==========================================
# Install required packages
# ==========================================

info "Installing required packages..."

apt-get install -y \
    ca-certificates \
    curl \
    git \
    unzip \
    build-essential \
    g++ \
    pkg-config \
    avrdude \
    apache2 \
    php-cli \
    php-curl \
    php-mbstring \
    php-xml \
    php-zip

success "Required packages installed."

# ==========================================
# Verify PHP
# ==========================================

info "Checking PHP..."

command_exists php ||
    die "PHP was not installed."

success "PHP: $(php --version | head -n 1)"

# ==========================================
# Verify g++
# ==========================================

info "Checking C++ compiler..."

command_exists g++ ||
    die "g++ was not installed."

success "g++: $(g++ --version | head -n 1)"

# ==========================================
# Verify avrdude
# ==========================================

info "Checking avrdude..."

command_exists avrdude ||
    die "avrdude was not installed."

success "avrdude installed."

# ==========================================
# Verify Apache
# ==========================================

info "Checking Apache..."

command_exists apache2ctl ||
    die "Apache was not installed."

success "Apache installed."

# ==========================================
# Verify required commands
# ==========================================

info "Verifying installed tools..."

REQUIRED_COMMANDS=(
    curl
    git
    unzip
    gcc
    g++
    php
    avrdude
    apache2ctl
)

for command in "${REQUIRED_COMMANDS[@]}"; do
    command_exists "$command" ||
        die "Required command '$command' is not available."
done

success "All required system tools are available."

# ==========================================
# Summary
# ==========================================

echo
echo "=============================================="
echo " Samaritan - Stage 1 Installation Complete"
echo "=============================================="
echo
echo "Installed:"
echo "  Apache"
echo "  PHP"
echo "  g++"
echo "  avrdude"
echo
echo "The Raspberry Pi is prepared to:"
echo "  - serve the React/PHP application"
echo "  - compile the C++ daemon"
echo "  - upload firmware to the Arduino"
echo
echo "The Pi does NOT require:"
echo "  - Node.js"
echo "  - npm"
echo "  - Python"
echo "  - pipx"
echo "  - PlatformIO"
echo "  - Composer"
echo
echo "Stage 1 has NOT:"
echo "  - configured Apache"
echo "  - configured systemd"
echo "  - deployed Samaritan"
echo "  - uploaded Arduino firmware"
echo
echo "=============================================="