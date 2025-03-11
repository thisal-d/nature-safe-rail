class TrainGpsDevice:
    devices = []
    
    @staticmethod
    def is_device_exist(device_id):
        for device in TrainGpsDevice.devices:
            # print("DEVICE ID :", device.get_device_id())
            if device.get_device_id() == device_id:
                return True
        return False
    
    @staticmethod
    def get_device(device_id):
        for device in TrainGpsDevice.devices:
            if device.get_device_id() == device_id:
                return device
            
    @staticmethod
    def get_all_devices():
        """Returns all devices as a list of dictionaries."""
        all_devices = []
        for device in TrainGpsDevice.devices:
            all_devices.append({
                "device_id": device.get_device_id(),
                "latitude": device.get_latitude(),
                "longitude": device.get_longitude()
            })
        # print(all_devices)
        return all_devices
    
    
    def __init__(self, id, latitude, longitude):
        self._device_id = id
        self._latitude = latitude
        self._longitude = longitude
        TrainGpsDevice.devices.append(self)
        
    def get_device_id(self):
        return self._device_id

    def get_latitude(self):
        return self._latitude
    
    def get_longitude(self):
        return self._longitude
    
    def set_latitude(self, latitude):
        self._latitude = latitude
    
    def set_longitude(self, longitude):
        self._longitude = longitude
    
    """
    
    def display(self):
        print("========================== Train GPS Device ==========================")
        print("Deice ID :",self._device_id)
        print("Latitude: ",self._latitude)
        print("Longitude: ",self._longitude)
        print("======================================================================")
    """
        