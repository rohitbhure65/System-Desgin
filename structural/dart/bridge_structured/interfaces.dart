abstract class DrawingAPI {
  void drawCircle(double x, double y, double radius);
  void drawRectangle(double x, double y, double width, double height);
}

abstract class Device {
  void turnOn();
  void turnOff();
  void setVolume(int volume);
  int getVolume();
}
