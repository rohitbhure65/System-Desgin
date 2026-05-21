import { StockObserver } from './interfaces';

export class StockMarket {
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

export class Investor implements StockObserver {
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

export class TradingBot implements StockObserver {
  onStockPriceChange(symbol: string, price: number): void {
    console.log(`  [TradingBot] Analyzing ${symbol} at $${price}`);
    if (price > 100) {
      console.log('  [TradingBot] Recommendation: SELL');
    } else if (price < 50) {
      console.log('  [TradingBot] Recommendation: BUY');
    }
  }
}
