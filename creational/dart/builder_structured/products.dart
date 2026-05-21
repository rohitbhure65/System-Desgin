class House {
  String _foundation = '';
  String _structure = '';
  String _roof = '';
  String _interior = '';
  bool _hasGarage = false;
  bool _hasGarden = false;
  bool _hasSwimmingPool = false;
  
  void setFoundation(String f) => _foundation = f;
  void setStructure(String s) => _structure = s;
  void setRoof(String r) => _roof = r;
  void setInterior(String i) => _interior = i;
  void setGarage(bool g) => _hasGarage = g;
  void setGarden(bool g) => _hasGarden = g;
  void setSwimmingPool(bool s) => _hasSwimmingPool = s;
  
  void display() {
    print('=== House Details ===');
    print('Foundation: $_foundation');
    print('Structure: $_structure');
    print('Roof: $_roof');
    print('Interior: $_interior');
    print('Garage: ${_hasGarage ? 'Yes' : 'No'}');
    print('Garden: ${_hasGarden ? 'Yes' : 'No'}');
    print('Swimming Pool: ${_hasSwimmingPool ? 'Yes' : 'No'}');
    print('====================');
  }
}

class Computer {
  String _cpu = '';
  String _gpu = '';
  int _ram = 8;
  int _storage = 256;
  bool _hasWifi = false;
  bool _hasBluetooth = false;
  
  void setCpu(String cpu) => _cpu = cpu;
  void setGpu(String gpu) => _gpu = gpu;
  void setRam(int ram) => _ram = ram;
  void setStorage(int storage) => _storage = storage;
  void setWifi(bool wifi) => _hasWifi = wifi;
  void setBluetooth(bool bluetooth) => _hasBluetooth = bluetooth;
  
  void display() {
    print('=== Computer Specs ===');
    print('CPU: $_cpu');
    print('GPU: $_gpu');
    print('RAM: $_ram GB');
    print('Storage: $_storage GB');
    print('WiFi: ${_hasWifi ? 'Yes' : 'No'}');
    print('Bluetooth: ${_hasBluetooth ? 'Yes' : 'No'}');
    print('=====================');
  }
}
