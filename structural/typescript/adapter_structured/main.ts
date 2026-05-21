import { PaymentProcessor } from './interfaces';
import { StripeAdapter, PayPalAdapter, TemperatureAdapter } from './adapters';
import { AudioPlayer } from './client';

function demoAdapter(): void {
  console.log('=== Adapter Pattern Demo ===\n');
  
  console.log('--- Media Player Adapter ---');
  const audioPlayer = new AudioPlayer();
  audioPlayer.play('mp3', 'beyond the horizon.mp3');
  audioPlayer.play('mp4', 'alone again.mp4');
  audioPlayer.play('vlc', 'far far away.vlc');
  audioPlayer.play('avi', 'mind me.avi');
  console.log();
  
  console.log('--- Payment Processing Adapter ---');
  const stripeAdapter: PaymentProcessor = new StripeAdapter();
  stripeAdapter.processPayment(100.50);
  const payPalAdapter: PaymentProcessor = new PayPalAdapter();
  payPalAdapter.processPayment(75.25);
  console.log();
  
  console.log('--- Two-way Temperature Adapter ---');
  const tempAdapter = new TemperatureAdapter();
  tempAdapter.setTemperatureInCelsius(25.0);
  console.log(`Temperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C`);
  console.log(`Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F`);
  
  tempAdapter.setTemperatureInFahrenheit(77.0);
  console.log(`\nTemperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C`);
  console.log(`Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F`);
}

demoAdapter();
