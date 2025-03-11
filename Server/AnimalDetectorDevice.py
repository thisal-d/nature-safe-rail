class AnimalDetectorDevice:
    device = []
    
    @staticmethod
    def is_device_exist(device_id):
        for device in AnimalDetectorDevice.device:
            # print("DEVICE ID :", device.get_device_id())
            if device.get_device_id() == device_id:
                return True
        return False
    
    @staticmethod
    def get_device(device_id):
        for device in AnimalDetectorDevice.device:
            if device.get_device_id() == device_id:
                return device
            
    @staticmethod
    def get_all_devices():
        """Returns all devices as a list of dictionaries."""
        all_devices = []
        for device in AnimalDetectorDevice.device:
            all_devices.append({
                "device_id": device.get_device_id(),
                "latitude": device.get_latitude(),
                "longitude": device.get_longitude(),
                "location": device.get_location(),
                "is_animal_detected": device.get_detected(),
                "is_active": device.get_active_status(),
            })
        # print(all_devices)
        return all_devices
    
    def __init__(self, id, latitude, longitude, location):
        self._device_id = id
        self._latitude = latitude
        self._longitude = longitude
        self._location = location
        self._is_animal_detected = None
        self._is_active = True
        self._is_issue_detected = True
        self._time = 0        
        AnimalDetectorDevice.device.append(self)
    
    def set_latitude(self, latitude):
        self._latitude = latitude
    
    def set_longitude(self, longitude):
        self._longitude = longitude
            
    def set_active_status(self, status):
        self._is_active = status

    def set_animal_detected_status(self, status):
        self._is_animal_detected = status
        
    def get_device_id(self):
        return self._device_id
    
    def get_detected(self):
        return self._is_animal_detected
    
    
    def get_active_status(self):
        return self._is_active
    
    def get_latitude(self):
        return self._latitude
    
    def get_longitude(self):
        return self._longitude

    def get_location(self):
        return self._location

    def set_location(self, location):
        self._location = location
    
    """
    def display(self):
        print("========================== Train GPS Device ==========================")
        print("Device ID :", self._device_id)
        print("Latitude: ", self._latitude)
        print("Longitude: ", self._longitude)
        print("Animal Detected: ", self._is_animal_detected)
        print("Time: ", self._time)
        print("======================================================================"
    """