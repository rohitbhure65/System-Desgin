import { MediaPlayer, PaymentProcessor, CelsiusTemperature, FahrenheitTemperature } from './interfaces';
import { AdvancedMediaPlayer, StripePaymentSystem, PayPalPaymentSystem } from './adaptees';

export class MediaAdapter implements MediaPlayer {
  private advancedMusicPlayer: AdvancedMediaPlayer;
  
  constructor() { this.advancedMusicPlayer = new AdvancedMediaPlayer(); }
  
  play(audioType: string, fileName: string): void {
    if (audioType === 'vlc') { this.advancedMusicPlayer.playVlc(fileName); }
    else if (audioType === 'mp4') { this.advancedMusicPlayer.playMp4(fileName); }
    else { console.log(`Invalid media. ${audioType} format not supported`); }
  }
}

export class StripeAdapter implements PaymentProcessor {
  private stripeSystem: StripePaymentSystem;
  constructor() { this.stripeSystem = new StripePaymentSystem(); }
  processPayment(amount: number): void { this.stripeSystem.makeStripePayment(amount); }
}

export class PayPalAdapter implements PaymentProcessor {
  private payPalSystem: PayPalPaymentSystem;
  constructor() { this.payPalSystem = new PayPalPaymentSystem(); }
  processPayment(amount: number): void { this.payPalSystem.sendPayPalRequest(amount); }
}

export class TemperatureAdapter implements CelsiusTemperature, FahrenheitTemperature {
  private temperatureInCelsius: number;
  constructor(temp: number = 0) { this.temperatureInCelsius = temp; }
  getTemperatureInCelsius(): number { return this.temperatureInCelsius; }
  setTemperatureInCelsius(temp: number): void { this.temperatureInCelsius = temp; }
  getTemperatureInFahrenheit(): number { return (this.temperatureInCelsius * 9 / 5) + 32; }
  setTemperatureInFahrenheit(temp: number): void { this.temperatureInCelsius = (temp - 32) * 5 / 9; }
}
