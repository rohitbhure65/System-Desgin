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
interface MediaPlayer {
  play(audioType: string, fileName: string): void;
}

// Adaptee - the class with an incompatible interface
class AdvancedMediaPlayer {
  playVlc(fileName: string): void {
    console.log(`Playing vlc file: ${fileName}`);
  }
  
  playMp4(fileName: string): void {
    console.log(`Playing mp4 file: ${fileName}`);
  }
}

// Adapter - makes the Adaptee's interface compatible with the Target interface
class MediaAdapter implements MediaPlayer {
  private advancedMusicPlayer: AdvancedMediaPlayer;
  
  constructor() {
    this.advancedMusicPlayer = new AdvancedMediaPlayer();
  }
  
  play(audioType: string, fileName: string): void {
    if (audioType === 'vlc') {
      this.advancedMusicPlayer.playVlc(fileName);
    } else if (audioType === 'mp4') {
      this.advancedMusicPlayer.playMp4(fileName);
    } else {
      console.log(`Invalid media. ${audioType} format not supported`);
    }
  }
}

// Client - uses the Target interface
class AudioPlayer implements MediaPlayer {
  private mediaAdapter?: MediaAdapter;
  
  play(audioType: string, fileName: string): void {
    // Built-in support for mp3
    if (audioType === 'mp3') {
      console.log(`Playing mp3 file: ${fileName}`);
    }
    // MediaAdapter provides support for other formats
    else if (audioType === 'vlc' || audioType === 'mp4') {
      this.mediaAdapter = new MediaAdapter();
      this.mediaAdapter.play(audioType, fileName);
    } else {
      console.log(`Invalid media. ${audioType} format not supported`);
    }
  }
}

// Example 2: Payment Processing Adapter
// This example shows a different scenario: payment processing

// Target Interface
interface PaymentProcessor {
  processPayment(amount: number): void;
}

// Adaptee - incompatible payment system
class StripePaymentSystem {
  makeStripePayment(amount: number): void {
    console.log(`Processing $${amount} via Stripe`);
  }
}

// Adaptee - another incompatible payment system
class PayPalPaymentSystem {
  sendPayPalRequest(amount: number): void {
    console.log(`Processing $${amount} via PayPal`);
  }
}

// Adapter for Stripe
class StripeAdapter implements PaymentProcessor {
  private stripeSystem: StripePaymentSystem;
  
  constructor() {
    this.stripeSystem = new StripePaymentSystem();
  }
  
  processPayment(amount: number): void {
    this.stripeSystem.makeStripePayment(amount);
  }
}

// Adapter for PayPal
class PayPalAdapter implements PaymentProcessor {
  private payPalSystem: PayPalPaymentSystem;
  
  constructor() {
    this.payPalSystem = new PayPalPaymentSystem();
  }
  
  processPayment(amount: number): void {
    this.payPalSystem.sendPayPalRequest(amount);
  }
}

// Example 3: Two-way Adapter
// Allows both interfaces to work with each other

// Interface A
interface CelsiusTemperature {
  getTemperatureInCelsius(): number;
  setTemperatureInCelsius(temp: number): void;
}

// Interface B
interface FahrenheitTemperature {
  getTemperatureInFahrenheit(): number;
  setTemperatureInFahrenheit(temp: number): void;
}

// Two-way adapter
class TemperatureAdapter implements CelsiusTemperature, FahrenheitTemperature {
  private temperatureInCelsius: number;
  
  constructor(temp: number = 0) {
    this.temperatureInCelsius = temp;
  }
  
  // Celsius interface implementation
  getTemperatureInCelsius(): number {
    return this.temperatureInCelsius;
  }
  
  setTemperatureInCelsius(temp: number): void {
    this.temperatureInCelsius = temp;
  }
  
  // Fahrenheit interface implementation
  getTemperatureInFahrenheit(): number {
    return (this.temperatureInCelsius * 9 / 5) + 32;
  }
  
  setTemperatureInFahrenheit(temp: number): void {
    this.temperatureInCelsius = (temp - 32) * 5 / 9;
  }
}

// Demo code
function demoAdapter(): void {
  console.log('=== Adapter Pattern Demo ===\n');
  
  // Example 1: Media Player Adapter
  console.log('--- Media Player Adapter ---');
  
  const audioPlayer = new AudioPlayer();
  
  audioPlayer.play('mp3', 'beyond the horizon.mp3');
  audioPlayer.play('mp4', 'alone again.mp4');
  audioPlayer.play('vlc', 'far far away.vlc');
  audioPlayer.play('avi', 'mind me.avi');
  
  console.log();
  
  // Example 2: Payment Processing Adapter
  console.log('--- Payment Processing Adapter ---');
  
  const stripeAdapter: PaymentProcessor = new StripeAdapter();
  stripeAdapter.processPayment(100.50);
  
  const payPalAdapter: PaymentProcessor = new PayPalAdapter();
  payPalAdapter.processPayment(75.25);
  
  console.log();
  
  // Example 3: Two-way Temperature Adapter
  console.log('--- Two-way Temperature Adapter ---');
  
  const tempAdapter = new TemperatureAdapter();
  
  // Set using Celsius interface
  tempAdapter.setTemperatureInCelsius(25.0);
  console.log(`Temperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C`);
  console.log(`Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F`);
  
  // Set using Fahrenheit interface
  tempAdapter.setTemperatureInFahrenheit(77.0);
  console.log(`\nTemperature in Celsius: ${tempAdapter.getTemperatureInCelsius()}°C`);
  console.log(`Temperature in Fahrenheit: ${tempAdapter.getTemperatureInFahrenheit()}°F`);
}

// Run the demo
demoAdapter();
