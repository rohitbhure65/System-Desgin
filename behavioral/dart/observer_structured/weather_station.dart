import 'interfaces.dart';

class WeatherStation {
  final List<WeatherObserver> _observers = [];
  double _temperature = 0;
  double _humidity = 0;
  double _pressure = 0;
  
  void addObserver(WeatherObserver observer) {
    _observers.add(observer);
  }
  
  void removeObserver(WeatherObserver observer) {
    _observers.remove(observer);
  }
  
  void setMeasurements(double temp, double hum, double press) {
    _temperature = temp;
    _humidity = hum;
    _pressure = press;
    print('\nWeather updated: $_temperature°C, $_humidity% humidity, $_pressure hPa');
    _notifyObservers();
  }
  
  void _notifyObservers() {
    for (final observer in _observers) {
      observer.onWeatherUpdate(_temperature, _humidity, _pressure);
    }
  }
}

class DisplayDevice implements WeatherObserver {
  final String _deviceName;
  
  DisplayDevice(this._deviceName);
  
  @override
  void onWeatherUpdate(double temperature, double humidity, double pressure) {
    print('  [$_deviceName] Displaying: $temperature°C, $humidity%, $pressure hPa');
  }
}

class AlertSystem implements WeatherObserver {
  @override
  void onWeatherUpdate(double temperature, double humidity, double pressure) {
    print('  [AlertSystem] Checking conditions...');
    if (temperature > 35) {
      print('  [AlertSystem] WARNING: High temperature!');
    }
    if (humidity > 80) {
      print('  [AlertSystem] WARNING: High humidity!');
    }
    if (pressure < 980) {
      print('  [AlertSystem] WARNING: Low pressure (storm coming)!');
    }
  }
}
