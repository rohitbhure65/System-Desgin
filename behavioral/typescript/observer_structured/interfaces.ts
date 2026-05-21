export interface Observer {
  update(message: string): void;
}

export abstract class Subject {
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

export interface StockObserver {
  onStockPriceChange(symbol: string, price: number): void;
}

export interface WeatherObserver {
  onWeatherUpdate(temperature: number, humidity: number, pressure: number): void;
}
