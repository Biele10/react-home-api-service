from flask import Flask, request, jsonify
import serial
import time
import json

app = Flask(__name__)


# TO-DO
# UPDATE REQUEST TO SEND COMMAND AS A STRING

# ---- SERIAL SETUP ----
STATIC_SERIAL_PORT = "/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_145313035343517071D1-if00"        # file name for arduino when plugged into raspberry pi
# SERIAL_PORT = "COM5"    # when testing locally
BAUD_RATE = 9600

try:
    arduino = serial.Serial(STATIC_SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # let Arduino reset
    print("Serial connected")
except Exception as e:
    print("Failed to connect to Arduino:", e)
    arduino = None

# Function that sends data to Arduino.
def send_to_arduino(request_type, message, params=None):
    if arduino and arduino.is_open:

        # stores like a json object
        payload = {
            "type": request_type,
            "command": message,
            "params": params or {}
        }

        command = (json.dumps(payload) + "\n").encode("utf-8")
        arduino.write(command)
        print("Sent:", message)
        return True
    return False

# Function that handles basic commands to send to the arduino.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
def send_command():
    command = request.args.get('command')

    if not command:
        return jsonify({"error": "missing command"}), 400

    requestType = 'command'     # tells the arduino that the given input is a simple command,
                                # bound to a particular function

    success = send_to_arduino(requestType, command)     # simple command, no params needed

    if success:
        return jsonify({'status': "sent", "command": command}), 200
    else:
        return jsonify({"error": "arduino not connected"}), 500

# API endpoint for PHP to send data to the arduino.
@app.route("/send", methods=["GET"])
def send():
    data = request.get_json()

    if not data or "command" not in data:
        return jsonify({"error": "missing command"}), 400

    command = data["command"]
    success = send_to_arduino(command)

    if success:
        return jsonify({"status": "sent", "command": command})
    else:
        return jsonify({"error": "arduino not connected"}), 500

# Main Program Loop
if __name__ == "__main__":
    # runs forever
    app.run(host="0.0.0.0", port=5000)