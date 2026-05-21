import 'interfaces.dart';
import 'adapters.dart';
import 'client.dart';

void main() {
  print('=== Adapter Pattern Demo ===\n');
  
  print('--- Media Player Adapter ---');
  var audioPlayer = AudioPlayer();
  audioPlayer.play('mp3', 'beyond the horizon.mp3');
  audioPlayer.play('mp4', 'alone again.mp4');
  audioPlayer.play('vlc', 'far far away.vlc');
  audioPlayer.play('avi', 'mind me.avi');
  print('');
  
  print('--- Payment Processing Adapter ---');
  PaymentProcessor stripeAdapter = StripeAdapter();
  stripeAdapter.processPayment(100.50);
  PaymentProcessor payPalAdapter = PayPalAdapter();
  payPalAdapter.processPayment(75.25);
  print('');
  
  print('--- Two-way Temperature Adapter ---');
  var tempAdapter = TemperatureAdapter();
  tempAdapter.setTemperatureInCelsius(25.0);
  print('Temperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C');
  print('Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F');
  
  tempAdapter.setTemperatureInFahrenheit(77.0);
  print('\nTemperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C');
  print('Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F');
}
