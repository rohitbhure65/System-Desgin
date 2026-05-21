import { WeatherObserver } from './interfaces';

export class WeatherStation {
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

export class DisplayDevice implements WeatherObserver {
  private deviceName: string;
  
  constructor(name: string) {
    this.deviceName = name;
  }
  
  onWeatherUpdate(temperature: number, humidity: number, pressure: number): void {
    console.log(`  [${this.deviceName}] Displaying: ${temperature}°C, ${humidity}%, ${pressure} hPa`);
  }
}

export class AlertSystem implements WeatherObserver {
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
