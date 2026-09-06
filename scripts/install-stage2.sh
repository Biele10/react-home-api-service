#!/usr/bin/env bash

# ==========================================
# Samaritan - Stage 2 Configuration
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
    die "This script must be run on Linux."

success "Linux detected."

# ==========================================
# Check root
# ==========================================

info "Checking root privileges..."

[[ "${EUID}" -eq 0 ]] ||
    die "Please run this script with sudo."

success "Running as root."

# ==========================================
# Check deployment user
# ==========================================

info "Checking for ubuntu user..."

id ubuntu >/dev/null 2>&1 ||
    die "User 'ubuntu' does not exist."

success "User 'ubuntu' found."

# ==========================================
# Check required tools
# ==========================================

info "Checking required system tools..."

REQUIRED_COMMANDS=(
    systemctl
    apache2ctl
)

for command in "${REQUIRED_COMMANDS[@]}"; do
    command_exists "$command" ||
        die "Required command '$command' is not available."
done

success "Required system tools are available."

# ==========================================
# Check configuration files
# ==========================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

SERVICE_SOURCE="${SCRIPT_DIR}/samaritan-daemon.service"
APACHE_SOURCE="${SCRIPT_DIR}/samaritan.conf"

info "Checking Samaritan configuration files..."

[[ -f "${SERVICE_SOURCE}" ]] ||
    die "Missing service file: ${SERVICE_SOURCE}"

[[ -f "${APACHE_SOURCE}" ]] ||
    die "Missing Apache configuration: ${APACHE_SOURCE}"

success "Samaritan configuration files found."

# ==========================================
# Create Samaritan directories
# ==========================================

info "Creating Samaritan directories..."

mkdir -p /var/www/Samaritan
mkdir -p /var/log/apache2

chown ubuntu:ubuntu /var/www/Samaritan

success "Samaritan directories prepared."

# ==========================================
# Configure Samaritan group
# ==========================================

info "Configuring Samaritan group..."

if ! getent group samaritan >/dev/null 2>&1; then
    groupadd samaritan
    info "Created 'samaritan' group."
else
    info "'samaritan' group already exists."
fi

usermod -aG samaritan ubuntu
usermod -aG samaritan www-data

success "Samaritan group configured."

# ==========================================
# Install systemd service
# ==========================================

info "Installing Samaritan systemd service..."

install -m 0644 \
    "${SERVICE_SOURCE}" \
    /etc/systemd/system/samaritan-daemon.service

systemctl daemon-reload

success "Samaritan systemd service installed."

# ==========================================
# Enable daemon
# ==========================================

info "Enabling Samaritan daemon..."

systemctl enable samaritan-daemon

success "Samaritan daemon enabled."

# ==========================================
# Install Apache configuration
# ==========================================

info "Installing Samaritan Apache configuration..."

install -m 0644 \
    "${APACHE_SOURCE}" \
    /etc/apache2/sites-available/samaritan.conf

success "Apache configuration installed."

# ==========================================
# Enable Apache rewrite module
# ==========================================

info "Enabling Apache rewrite module..."

a2enmod rewrite

success "Apache rewrite module enabled."

# ==========================================
# Enable Samaritan site
# ==========================================

info "Enabling Samaritan Apache site..."

a2ensite samaritan.conf

success "Samaritan Apache site enabled."

# ==========================================
# Disable default Apache site
# ==========================================

if [[ -e /etc/apache2/sites-enabled/000-default.conf ]]; then
    info "Disabling default Apache site..."

    a2dissite 000-default.conf

    success "Default Apache site disabled."
else
    info "Default Apache site is not enabled."
fi

# ==========================================
# Validate Apache configuration
# ==========================================

info "Validating Apache configuration..."

apache2ctl configtest

success "Apache configuration is valid."

# ==========================================
# Enable Apache
# ==========================================

info "Enabling Apache..."

systemctl enable apache2

success "Apache enabled."

# ==========================================
# Restart Apache
# ==========================================

info "Restarting Apache..."

systemctl restart apache2

success "Apache is running."

# ==========================================
# Daemon status
# ==========================================

if [[ -x /var/www/Samaritan/daemon/build/samaritan-daemon ]]; then
    warning "Samaritan daemon executable already exists."

    info "Starting Samaritan daemon..."

    systemctl restart samaritan-daemon

    success "Samaritan daemon started."
else
    info "Samaritan daemon executable does not exist yet."
    info "The daemon will be compiled during the first deployment."
fi

# ==========================================
# Summary
# ==========================================

echo
echo "=============================================="
echo " Samaritan - Stage 2 Configuration Complete"
echo "=============================================="
echo
echo "Configured:"
echo "  - Apache"
echo "  - Apache rewrite module"
echo "  - Samaritan Apache site"
echo "  - Samaritan systemd service"
echo "  - Samaritan runtime directory"
echo "  - Samaritan communication group"
echo
echo "Apache:"
echo "  DocumentRoot:"
echo "    /var/www/Samaritan/public_html"
echo
echo "Daemon:"
echo "  Service:"
echo "    samaritan-daemon"
echo
echo "  Executable:"
echo "    /var/www/Samaritan/daemon/build/samaritan-daemon"
echo
echo "  Socket:"
echo "    /run/samaritan/samaritan.sock"
echo
echo "The daemon will be started automatically"
echo "after its executable is created by deployment."
echo
echo "=============================================="