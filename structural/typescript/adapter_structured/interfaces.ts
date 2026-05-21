export interface MediaPlayer {
  play(audioType: string, fileName: string): void;
}

export interface PaymentProcessor {
  processPayment(amount: number): void;
}

export interface CelsiusTemperature {
  getTemperatureInCelsius(): number;
  setTemperatureInCelsius(temp: number): void;
}

export interface FahrenheitTemperature {
  getTemperatureInFahrenheit(): number;
  setTemperatureInFahrenheit(temp: number): void;
}
