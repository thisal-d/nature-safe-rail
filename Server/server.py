from flask import Flask, request, jsonify
from datetime import datetime
from AnimalDetectorDevice import AnimalDetectorDevice
from TrainGpsDevice import TrainGpsDevice
from flask_cors import CORS

# CONFIGURE SERVER IP ADDRESS and PORT ADDRESS
IP_ADDRESS = "XXX.XXX.XXX.XXX" # Replace with your ip address
PORT = 5000

app = Flask(__name__)

# Enable CORS
CORS(app)

# Dictionary to store device data (device_id -> data)
animal_detectors = []
train_gps = []

# Add two animal detector devices
animal_detectors.append(AnimalDetectorDevice(id=3, location="Katharagama", longitude=81.3353611, latitude=6.4169744))
animal_detectors.append(AnimalDetectorDevice(id=4, location="Panadura", longitude=79.94, latitude=6.713))
# API to receive status updates from devices
@app.route('/update_animal_detector_device_status', methods=['POST'])
def update_animal_detecor_status():
    # get json data
    data = request.json
    
    device_id = int(data.get('device_id'))
    if data.get('is_animal_detected') == "0":
        is_animal_detected = False
    else:
        is_animal_detected =True
    latitude = float(data.get('latitude'))
    longitude = float(data.get('longitude'))
    location = data.get('location')
    active_time = int(data.get('active_time'))
    # print("Device ID:", device_id, " | Animal detected:", is_animal_detected, " | Latitude:", latitude, " | Longitude:", longitude, " | Location:", location)

    # Check device is already exist
    if AnimalDetectorDevice.is_device_exist(device_id):
        device: AnimalDetectorDevice = AnimalDetectorDevice.get_device(device_id)
    else:
        device = AnimalDetectorDevice(id=device_id, longitude=longitude, latitude=latitude, location=location)
    # Update animal detected device data
    device.set_animal_detected_status(is_animal_detected)
    device.set_location(location)
    device.set_active_time(active_time)
    device.set_latitude(latitude)
    device.set_longitude(longitude)
    # print(AnimalDetectorDevice.get_all_devices())
    # for device in TrainGpsDevice.get_all_devices():
    #    device.display()
    return jsonify({'message': 'Status updated successfully'}), 200

# API to receive status updates from devices
@app.route('/update_train_gps_device_status', methods=['POST'])
def update_train_gps_status():
    data = request.json
    device_id = int(data.get('device_id'))
    latitude = float(data.get('latitude'))
    longitude = float(data.get('longitude'))
    
    # print("Device ID:", device_id, " | Animal detected:", is_animal_detected, " | Latitude:", latitude, " | Longitude:", longitude, " | Location:", location)
    
    # Check GPS device already exist
    if TrainGpsDevice.is_device_exist(device_id):
        device: TrainGpsDevice = TrainGpsDevice.get_device(device_id)
    else:
        device: TrainGpsDevice = TrainGpsDevice(id=device_id, longitude=longitude, latitude=latitude)
    # Set GPS device data
    device.set_latitude(latitude)
    device.set_longitude(longitude)
    # print(TrainGpsDevice.get_all_devices())
    
    # for device in TrainGpsDevice.get_all_devices():
    #    device.display()
    return jsonify({'message': 'Status updated successfully'}), 200

# API to get all device statuses (For the train device)
@app.route('/get_animal_detecting_status', methods=['GET'])
def get_animal_detecting_status():
    # print(AnimalDetectorDevice.get_all_devices())
    return jsonify(AnimalDetectorDevice.get_all_devices()), 200

# API to get all device statuses (For the gps device)
@app.route('/get_gps_status', methods=['GET'])
def get_animal_ditecting_status():
    # print(TrainGpsDevice.get_all_devices())
    return jsonify(TrainGpsDevice.get_all_devices()), 200

if __name__ == '__main__':
    app.run(debug=True, host=IP_ADDRESS, port=PORT)
