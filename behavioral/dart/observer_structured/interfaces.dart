abstract class Observer {
  void update(String message);
}

abstract class Subject {
  final List<Observer> _observers = [];
  
  void attach(Observer observer) {
    _observers.add(observer);
    print('Attached an observer');
  }
  
  void detach(Observer observer) {
    _observers.remove(observer);
    print('Detached an observer');
  }
  
  void notify(String message) {
    print('Notifying observers...');
    for (final observer in _observers) {
      observer.update(message);
    }
  }
}

abstract class StockObserver {
  void onStockPriceChange(String symbol, double price);
}

abstract class WeatherObserver {
  void onWeatherUpdate(double temperature, double humidity, double pressure);
}
