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
interface Observer {
  update(message: string): void;
}

// Subject interface - declares methods for attaching, detaching, and notifying observers
abstract class Subject {
  protected observers: Observer[] = [];
  
  attach(observer: Observer): void {
    this.observers.push(observer);
    console.log('Attached an observer');
  }
  
  detach(observer: Observer): void {
    const index = this.observers.indexOf(observer);
    if (index !== -1) {
      this.observers.splice(index, 1);
      console.log('Detached an observer');
    }
  }
  
  notify(message: string): void {
    console.log('Notifying observers...');
    for (const observer of this.observers) {
      observer.update(message);
    }
  }
}

// Concrete Subject
class YouTubeChannel extends Subject {
  private channelName: string;
  
  constructor(name: string) {
    super();
    this.channelName = name;
  }
  
  uploadVideo(videoTitle: string): void {
    console.log(`\n${this.channelName} uploaded: ${videoTitle}`);
    this.notify(`New video: ${videoTitle}`);
  }
  
  goLive(streamTitle: string): void {
    console.log(`\n${this.channelName} is live: ${streamTitle}`);
    this.notify(`Live stream started: ${streamTitle}`);
  }
}

// Concrete Observer 1
class Subscriber implements Observer {
  private name: string;
  
  constructor(name: string) {
    this.name = name;
  }
  
  update(message: string): void {
    console.log(`  ${this.name} received notification: ${message}`);
  }
}

// Concrete Observer 2
class NotificationService implements Observer {
  update(message: string): void {
    console.log(`  [NotificationService] Push notification sent: ${message}`);
  }
}

// Example 2: Stock Market
// Shows how Observer can be used for real-time updates

interface StockObserver {
  onStockPriceChange(symbol: string, price: number): void;
}

class StockMarket {
  private observers: StockObserver[] = [];
  private stockPrices: Map<string, number> = new Map();
  
  addObserver(observer: StockObserver): void {
    this.observers.push(observer);
  }
  
  removeObserver(observer: StockObserver): void {
    const index = this.observers.indexOf(observer);
    if (index !== -1) {
      this.observers.splice(index, 1);
    }
  }
  
  updateStockPrice(symbol: string, price: number): void {
    this.stockPrices.set(symbol, price);
    console.log(`\n${symbol} price updated to $${price}`);
    this.notifyObservers(symbol, price);
  }
  
  private notifyObservers(symbol: string, price: number): void {
    for (const observer of this.observers) {
      observer.onStockPriceChange(symbol, price);
    }
  }
}

class Investor implements StockObserver {
  private name: string;
  private portfolio: Map<string, number> = new Map();
  
  constructor(name: string) {
    this.name = name;
  }
  
  buyStock(symbol: string, shares: number): void {
    const current = this.portfolio.get(symbol) || 0;
    this.portfolio.set(symbol, current + shares);
    console.log(`${this.name} bought ${shares} shares of ${symbol}`);
  }
  
  onStockPriceChange(symbol: string, price: number): void {
    const shares = this.portfolio.get(symbol);
    if (shares !== undefined && shares > 0) {
      console.log(`  ${this.name} owns ${shares} shares of ${symbol} (current price: $${price})`);
    }
  }
}

class TradingBot implements StockObserver {
  onStockPriceChange(symbol: string, price: number): void {
    console.log(`  [TradingBot] Analyzing ${symbol} at $${price}`);
    if (price > 100) {
      console.log('  [TradingBot] Recommendation: SELL');
    } else if (price < 50) {
      console.log('  [TradingBot] Recommendation: BUY');
    }
  }
}

// Example 3: Weather Station
// Shows how Observer can be used for sensor data

interface WeatherObserver {
  onWeatherUpdate(temperature: number, humidity: number, pressure: number): void;
}

class WeatherStation {
  private observers: WeatherObserver[] = [];
  private temperature: number = 0;
  private humidity: number = 0;
  private pressure: number = 0;
  
  addObserver(observer: WeatherObserver): void {
    this.observers.push(observer);
  }
  
  removeObserver(observer: WeatherObserver): void {
    const index = this.observers.indexOf(observer);
    if (index !== -1) {
      this.observers.splice(index, 1);
    }
  }
  
  setMeasurements(temp: number, hum: number, press: number): void {
    this.temperature = temp;
    this.humidity = hum;
    this.pressure = press;
    console.log(`\nWeather updated: ${this.temperature}°C, ${this.humidity}% humidity, ${this.pressure} hPa`);
    this.notifyObservers();
  }
  
  private notifyObservers(): void {
    for (const observer of this.observers) {
      observer.onWeatherUpdate(this.temperature, this.humidity, this.pressure);
    }
  }
}

class DisplayDevice implements WeatherObserver {
  private deviceName: string;
  
  constructor(name: string) {
    this.deviceName = name;
  }
  
  onWeatherUpdate(temperature: number, humidity: number, pressure: number): void {
    console.log(`  [${this.deviceName}] Displaying: ${temperature}°C, ${humidity}%, ${pressure} hPa`);
  }
}

class AlertSystem implements WeatherObserver {
  onWeatherUpdate(temperature: number, humidity: number, pressure: number): void {
    console.log('  [AlertSystem] Checking conditions...');
    if (temperature > 35) {
      console.log('  [AlertSystem] WARNING: High temperature!');
    }
    if (humidity > 80) {
      console.log('  [AlertSystem] WARNING: High humidity!');
    }
    if (pressure < 980) {
      console.log('  [AlertSystem] WARNING: Low pressure (storm coming)!');
    }
  }
}

// Demo code
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
