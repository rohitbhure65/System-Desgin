import 'interfaces.dart';

class SmartDevice {
  final Mediator _homeHub;
  final String _deviceName;
  bool _isOn = false;
  
  SmartDevice(this._homeHub, this._deviceName);
  
  void turnOn() {
    _isOn = true;
    print('$_deviceName turned ON');
    _homeHub.sendMessage('$_deviceName turned ON', _deviceName);
  }
  
  void turnOff() {
    _isOn = false;
    print('$_deviceName turned OFF');
    _homeHub.sendMessage('$_deviceName turned OFF', _deviceName);
  }
  
  String get name => _deviceName;
  
  bool get isOn => _isOn;
}

class SmartLight extends SmartDevice {
  SmartLight(super.homeHub, super.name);
}

class SmartThermostat extends SmartDevice {
  int _temperature = 70;
  
  SmartThermostat(super.homeHub, super.name);
  
  void setTemperature(int temp) {
    _temperature = temp;
    print('$name set to $_temperature°F');
  }
  
  int get temperature => _temperature;
}

class HomeHub implements Mediator {
  final Map<String, SmartDevice> _devices = {};
  
  void addDevice(SmartDevice device) {
    _devices[device.name] = device;
  }
  
  @override
  void sendMessage(String message, String sender) {
    print('Home Hub: $message');
    
    if (sender.contains('Thermostat') && message.contains('turned ON')) {
      for (final device in _devices.values) {
        if (device.name.contains('Light') && !device.isOn) {
          device.turnOn();
        }
      }
    }
  }
  
  void activateAwayMode() {
    print('Home Hub: Activating away mode...');
    for (final device in _devices.values) {
      if (device.isOn) {
        device.turnOff();
      }
    }
  }
  
  void activateHomeMode() {
    print('Home Hub: Activating home mode...');
    for (final device in _devices.values) {
      if (device.name.contains('Light')) {
        device.turnOn();
      }
    }
  }
}
