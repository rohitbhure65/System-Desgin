/*
 * OBSERVER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Observer pattern defines a subscription mechanism to notify multiple objects about any events that happen to the object they are observing.
 * It establishes a one-to-many dependency between objects so that when one object changes state, all its dependents are notified.
 * 
 * WHY DOES IT EXIST?
 * - When you need to notify multiple objects about changes to a single object
 * - When you want to decouple the subject from its observers
 * - When you want to broadcast changes to multiple subscribers dynamically
 * 
 * WHEN TO USE IT?
 * - When changes to one object require changing other objects
 * - When the set of objects that need to be notified is unknown or dynamic
 * - When you want to implement a publish-subscribe model
 * - Common use cases: GUI event handling, news feeds, social media notifications, stock price updates
 * 
 * PROS:
 * - Open/Closed Principle (can add new observers without changing the subject)
 * - Establishes loose coupling between subject and observers
 * - Can broadcast communications to multiple objects
 * - Supports dynamic subscription/unsubscription
 * 
 * CONS:
 * - Can lead to unexpected updates if observers are not careful
 * - Can cause performance issues with many observers
 * - Debugging can be difficult due to indirect calls
 * - May cause memory leaks if observers don't unsubscribe
 * 
 * REAL-WORLD ANALOGY:
 * Think of a YouTube channel (subject) and subscribers (observers). When the channel uploads a new video, all subscribers get notified. Subscribers can subscribe or unsubscribe at any time. The channel doesn't need to know who is subscribed - it just broadcasts notifications to all current subscribers.
 */

// Observer interface - declares the update method
abstract class Observer {
  void update(String message);
}

// Subject interface - declares methods for attaching, detaching, and notifying observers
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

// Concrete Subject
class YouTubeChannel extends Subject {
  final String _channelName;
  
  YouTubeChannel(this._channelName);
  
  void uploadVideo(String videoTitle) {
    print('\n$_channelName uploaded: $videoTitle');
    notify('New video: $videoTitle');
  }
  
  void goLive(String streamTitle) {
    print('\n$_channelName is live: $streamTitle');
    notify('Live stream started: $streamTitle');
  }
}

// Concrete Observer 1
class Subscriber implements Observer {
  final String _name;
  
  Subscriber(this._name);
  
  @override
  void update(String message) {
    print('  $_name received notification: $message');
  }
}

// Concrete Observer 2
class NotificationService implements Observer {
  @override
  void update(String message) {
    print('  [NotificationService] Push notification sent: $message');
  }
}

// Example 2: Stock Market
// Shows how Observer can be used for real-time updates

abstract class StockObserver {
  void onStockPriceChange(String symbol, double price);
}

class StockMarket {
  final List<StockObserver> _observers = [];
  final Map<String, double> _stockPrices = {};
  
  void addObserver(StockObserver observer) {
    _observers.add(observer);
  }
  
  void removeObserver(StockObserver observer) {
    _observers.remove(observer);
  }
  
  void updateStockPrice(String symbol, double price) {
    _stockPrices[symbol] = price;
    print('\n$symbol price updated to \$$price');
    _notifyObservers(symbol, price);
  }
  
  void _notifyObservers(String symbol, double price) {
    for (final observer in _observers) {
      observer.onStockPriceChange(symbol, price);
    }
  }
}

class Investor implements StockObserver {
  final String _name;
  final Map<String, int> _portfolio = {};
  
  Investor(this._name);
  
  void buyStock(String symbol, int shares) {
    _portfolio[symbol] = (_portfolio[symbol] ?? 0) + shares;
    print('$_name bought $shares shares of $symbol');
  }
  
  @override
  void onStockPriceChange(String symbol, double price) {
    final shares = _portfolio[symbol];
    if (shares != null && shares > 0) {
      print('  $_name owns $shares shares of $symbol (current price: \$$price)');
    }
  }
}

class TradingBot implements StockObserver {
  @override
  void onStockPriceChange(String symbol, double price) {
    print('  [TradingBot] Analyzing $symbol at \$$price');
    if (price > 100) {
      print('  [TradingBot] Recommendation: SELL');
    } else if (price < 50) {
      print('  [TradingBot] Recommendation: BUY');
    }
  }
}

// Example 3: Weather Station
// Shows how Observer can be used for sensor data

abstract class WeatherObserver {
  void onWeatherUpdate(double temperature, double humidity, double pressure);
}

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

// Demo code
void main() {
  print('=== Observer Pattern Demo ===\n');
  
  // Example 1: YouTube Channel
  print('--- YouTube Channel Example ---');
  
  final channel = YouTubeChannel('Tech Channel');
  
  final subscriber1 = Subscriber('Alice');
  final subscriber2 = Subscriber('Bob');
  final notificationService = NotificationService();
  
  channel.attach(subscriber1);
  channel.attach(subscriber2);
  channel.attach(notificationService);
  
  channel.uploadVideo('Design Patterns Tutorial');
  
  channel.detach(subscriber2);
  
  channel.goLive('Live Q&A Session');
  
  print('');
  
  // Example 2: Stock Market
  print('--- Stock Market Example ---');
  
  final market = StockMarket();
  
  final investor1 = Investor('John');
  final investor2 = Investor('Jane');
  final tradingBot = TradingBot();
  
  market.addObserver(investor1);
  market.addObserver(investor2);
  market.addObserver(tradingBot);
  
  investor1.buyStock('AAPL', 100);
  investor2.buyStock('GOOGL', 50);
  
  market.updateStockPrice('AAPL', 150.50);
  market.updateStockPrice('GOOGL', 45.00);
  market.updateStockPrice('TSLA', 200.00);
  
  print('');
  
  // Example 3: Weather Station
  print('--- Weather Station Example ---');
  
  final station = WeatherStation();
  
  final phoneDisplay = DisplayDevice('Phone');
  final watchDisplay = DisplayDevice('Smart Watch');
  final alertSystem = AlertSystem();
  
  station.addObserver(phoneDisplay);
  station.addObserver(watchDisplay);
  station.addObserver(alertSystem);
  
  station.setMeasurements(25.0, 60.0, 1013.0);
  station.setMeasurements(38.0, 85.0, 975.0);
  station.setMeasurements(20.0, 50.0, 1020.0);
}
