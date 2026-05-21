import 'interfaces.dart';
import 'adaptees.dart';

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

class StripeAdapter implements PaymentProcessor {
  final StripePaymentSystem _stripeSystem = StripePaymentSystem();
  
  @override
  void processPayment(double amount) {
    _stripeSystem.makeStripePayment(amount);
  }
}

class PayPalAdapter implements PaymentProcessor {
  final PayPalPaymentSystem _payPalSystem = PayPalPaymentSystem();
  
  @override
  void processPayment(double amount) {
    _payPalSystem.sendPayPalRequest(amount);
  }
}

class TemperatureAdapter implements CelsiusTemperature, FahrenheitTemperature {
  double _temperatureInCelsius;
  
  TemperatureAdapter([this._temperatureInCelsius = 0.0]);
  
  @override
  double getTemperatureInCelsius() {
    return _temperatureInCelsius;
  }
  
  @override
  void setTemperatureInCelsius(double temp) {
    _temperatureInCelsius = temp;
  }
  
  @override
  double getTemperatureInFahrenheit() {
    return (_temperatureInCelsius * 9 / 5) + 32;
  }
  
  @override
  void setTemperatureInFahrenheit(double temp) {
    _temperatureInCelsius = (temp - 32) * 5 / 9;
  }
}
