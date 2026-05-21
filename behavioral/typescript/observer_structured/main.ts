import { YouTubeChannel, Subscriber, NotificationService } from './youtube_channel';
import { StockMarket, Investor, TradingBot } from './stock_market';
import { WeatherStation, DisplayDevice, AlertSystem } from './weather_station';

console.log('=== Observer Pattern Demo ===\n');

// Example 1: YouTube Channel
console.log('--- YouTube Channel Example ---');

const channel = new YouTubeChannel('Tech Channel');

const subscriber1 = new Subscriber('Alice');
const subscriber2 = new Subscriber('Bob');
const notificationService = new NotificationService();

channel.attach(subscriber1);
channel.attach(subscriber2);
channel.attach(notificationService);

channel.uploadVideo('Design Patterns Tutorial');

channel.detach(subscriber2);

channel.goLive('Live Q&A Session');

console.log('');

// Example 2: Stock Market
console.log('--- Stock Market Example ---');

const market = new StockMarket();

const investor1 = new Investor('John');
const investor2 = new Investor('Jane');
const tradingBot = new TradingBot();

market.addObserver(investor1);
market.addObserver(investor2);
market.addObserver(tradingBot);

investor1.buyStock('AAPL', 100);
investor2.buyStock('GOOGL', 50);

market.updateStockPrice('AAPL', 150.50);
market.updateStockPrice('GOOGL', 45.00);
market.updateStockPrice('TSLA', 200.00);

console.log('');

// Example 3: Weather Station
console.log('--- Weather Station Example ---');

const station = new WeatherStation();

const phoneDisplay = new DisplayDevice('Phone');
const watchDisplay = new DisplayDevice('Smart Watch');
const alertSystem = new AlertSystem();

station.addObserver(phoneDisplay);
station.addObserver(watchDisplay);
station.addObserver(alertSystem);

station.setMeasurements(25.0, 60.0, 1013.0);
station.setMeasurements(38.0, 85.0, 975.0);
station.setMeasurements(20.0, 50.0, 1020.0);
