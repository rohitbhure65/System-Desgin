/*
 * ADAPTER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Adapter pattern allows objects with incompatible interfaces to collaborate. It acts as a bridge between two incompatible interfaces.
 * 
 * WHY DOES IT EXIST?
 * - When you want to use an existing class whose interface doesn't match the one you need
 * - When you want to create a reusable class that cooperates with unrelated classes with incompatible interfaces
 * - When you need to use several existing subclasses, but adapting each to match your interface would be impractical
 * 
 * WHEN TO USE IT?
 * - When you want to use a third-party class but its interface doesn't match your system's interface
 * - When you need to integrate new components into an existing system without modifying existing code
 * - When you want to reuse existing classes that have similar functionality but different interfaces
 * - Common use cases: integrating third-party libraries, legacy code integration, data format conversion
 * 
 * PROS:
 * - Single Responsibility Principle (separates conversion logic from business logic)
 * - Open/Closed Principle (introduce new adapters without modifying existing code)
 * - Allows incompatible classes to work together
 * - Improves code reusability
 * 
 * CONS:
 * - Increases overall code complexity
 * - Can introduce additional layers of indirection
 * - May not be suitable for simple cases where direct modification is easier
 * - Can make the code harder to understand due to multiple layers
 * 
 * REAL-WORLD ANALOGY:
 * Think of a power adapter when traveling abroad. Your device (client) expects a certain plug shape (target interface), but the wall outlet (adaptee) has a different shape. The adapter converts between the two, allowing your device to work with the foreign outlet without modifying either the device or the wall.
 */

// Target Interface - the interface that the client expects
abstract class MediaPlayer {
  void play(String audioType, String fileName);
}

// Adaptee - the class with an incompatible interface
class AdvancedMediaPlayer {
  void playVlc(String fileName) {
    print('Playing vlc file: $fileName');
  }
  
  void playMp4(String fileName) {
    print('Playing mp4 file: $fileName');
  }
}

// Adapter - makes the Adaptee's interface compatible with the Target interface
class MediaAdapter implements MediaPlayer {
  final AdvancedMediaPlayer _advancedMusicPlayer = AdvancedMediaPlayer();
  
  @override
  void play(String audioType, String fileName) {
    if (audioType == 'vlc') {
      _advancedMusicPlayer.playVlc(fileName);
    } else if (audioType == 'mp4') {
      _advancedMusicPlayer.playMp4(fileName);
    } else {
      print('Invalid media. $audioType format not supported');
    }
  }
}

// Client - uses the Target interface
class AudioPlayer implements MediaPlayer {
  MediaAdapter? _mediaAdapter;
  
  @override
  void play(String audioType, String fileName) {
    // Built-in support for mp3
    if (audioType == 'mp3') {
      print('Playing mp3 file: $fileName');
    }
    // MediaAdapter provides support for other formats
    else if (audioType == 'vlc' || audioType == 'mp4') {
      _mediaAdapter = MediaAdapter();
      _mediaAdapter!.play(audioType, fileName);
    } else {
      print('Invalid media. $audioType format not supported');
    }
  }
}

// Example 2: Payment Processing Adapter
// This example shows a different scenario: payment processing

// Target Interface
abstract class PaymentProcessor {
  void processPayment(double amount);
}

// Adaptee - incompatible payment system
class StripePaymentSystem {
  void makeStripePayment(double amount) {
    print('Processing \$$amount via Stripe');
  }
}

// Adaptee - another incompatible payment system
class PayPalPaymentSystem {
  void sendPayPalRequest(double amount) {
    print('Processing \$$amount via PayPal');
  }
}

// Adapter for Stripe
class StripeAdapter implements PaymentProcessor {
  final StripePaymentSystem _stripeSystem = StripePaymentSystem();
  
  @override
  void processPayment(double amount) {
    _stripeSystem.makeStripePayment(amount);
  }
}

// Adapter for PayPal
class PayPalAdapter implements PaymentProcessor {
  final PayPalPaymentSystem _payPalSystem = PayPalPaymentSystem();
  
  @override
  void processPayment(double amount) {
    _payPalSystem.sendPayPalRequest(amount);
  }
}

// Example 3: Two-way Adapter
// Allows both interfaces to work with each other

// Interface A
abstract class CelsiusTemperature {
  double getTemperatureInCelsius();
  void setTemperatureInCelsius(double temp);
}

// Interface B
abstract class FahrenheitTemperature {
  double getTemperatureInFahrenheit();
  void setTemperatureInFahrenheit(double temp);
}

// Two-way adapter
class TemperatureAdapter implements CelsiusTemperature, FahrenheitTemperature {
  double _temperatureInCelsius;
  
  TemperatureAdapter([this._temperatureInCelsius = 0.0]);
  
  // Celsius interface implementation
  @override
  double getTemperatureInCelsius() {
    return _temperatureInCelsius;
  }
  
  @override
  void setTemperatureInCelsius(double temp) {
    _temperatureInCelsius = temp;
  }
  
  // Fahrenheit interface implementation
  @override
  double getTemperatureInFahrenheit() {
    return (_temperatureInCelsius * 9 / 5) + 32;
  }
  
  @override
  void setTemperatureInFahrenheit(double temp) {
    _temperatureInCelsius = (temp - 32) * 5 / 9;
  }
}

// Demo code
void main() {
  print('=== Adapter Pattern Demo ===\n');
  
  // Example 1: Media Player Adapter
  print('--- Media Player Adapter ---');
  
  var audioPlayer = AudioPlayer();
  
  audioPlayer.play('mp3', 'beyond the horizon.mp3');
  audioPlayer.play('mp4', 'alone again.mp4');
  audioPlayer.play('vlc', 'far far away.vlc');
  audioPlayer.play('avi', 'mind me.avi');
  
  print('');
  
  // Example 2: Payment Processing Adapter
  print('--- Payment Processing Adapter ---');
  
  PaymentProcessor stripeAdapter = StripeAdapter();
  stripeAdapter.processPayment(100.50);
  
  PaymentProcessor payPalAdapter = PayPalAdapter();
  payPalAdapter.processPayment(75.25);
  
  print('');
  
  // Example 3: Two-way Temperature Adapter
  print('--- Two-way Temperature Adapter ---');
  
  var tempAdapter = TemperatureAdapter();
  
  // Set using Celsius interface
  tempAdapter.setTemperatureInCelsius(25.0);
  print('Temperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C');
  print('Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F');
  
  // Set using Fahrenheit interface
  tempAdapter.setTemperatureInFahrenheit(77.0);
  print('\nTemperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C');
  print('Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F');
}
