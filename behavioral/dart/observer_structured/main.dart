import 'interfaces.dart';
import 'youtube_channel.dart';
import 'stock_market.dart';
import 'weather_station.dart';

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
