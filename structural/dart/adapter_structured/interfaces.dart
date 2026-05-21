abstract class MediaPlayer {
  void play(String audioType, String fileName);
}

abstract class PaymentProcessor {
  void processPayment(double amount);
}

abstract class CelsiusTemperature {
  double getTemperatureInCelsius();
  void setTemperatureInCelsius(double temp);
}

abstract class FahrenheitTemperature {
  double getTemperatureInFahrenheit();
  void setTemperatureInFahrenheit(double temp);
}
