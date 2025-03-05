from flask import Flask, request, jsonify
from datetime import datetime
from AnimalDetector import AnimalDetector
from flask_cors import CORS

# CONFIGURE SERVER 
IP_ADDRESS = "192.168.34.185" 
PORT = 5000


app = Flask(__name__)

# Enable CORS
CORS(app)

# Dictionary to store device data (device_id -> data)
animal_detectors = []

# API to receive status updates from devices
@app.route('/update_status', methods=['POST'])
def update_status():
    data = request.json
    device_id = int(data.get('device_id'))
    if data.get('is_animal_detected') == "0":
        is_animal_detected = False
    else:
        is_animal_detected =True
    latitude = float(data.get('latitude'))
    longitude = float(data.get('longitude'))
    location = data.get('location')
    
    # print("Device ID:", device_id, " | Animal detected:", is_animal_detected, " | Latitude:", latitude, " | Longitude:", longitude, " | Location:", location)
    
    if AnimalDetector.is_device_exist(device_id):
        device: AnimalDetector = AnimalDetector.get_device(device_id)
    else:
        device = AnimalDetector(id=device_id, longitude=longitude, latitide=latitude, location=location)
    device.set_animal_detected_status(is_animal_detected)

    return jsonify({'message': 'Status updated successfully'}), 200

# API to get all device statuses (For the train device)
@app.route('/get_status', methods=['GET'])
def get_status():
    print(AnimalDetector.get_all_devices())
    return jsonify(AnimalDetector.get_all_devices()), 200

if __name__ == '__main__':
    app.run(debug=True, host=IP_ADDRESS, port=PORT)
