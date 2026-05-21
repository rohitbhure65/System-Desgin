import 'interfaces.dart';

class Aircraft {
  final String _flightNumber;
  int _altitude = 0;
  
  Aircraft(this._flightNumber);
  
  void requestTakeoff() {
    print('$_flightNumber requesting takeoff clearance...');
  }
  
  void requestLanding() {
    print('$_flightNumber requesting landing clearance...');
  }
  
  void setAltitude(int alt) {
    _altitude = alt;
    print('$_flightNumber at altitude $_altitude feet');
  }
  
  String get flightNumber => _flightNumber;
}

class ControlTower implements Mediator {
  final Map<String, Aircraft> _aircrafts = {};
  
  void registerAircraft(Aircraft aircraft) {
    _aircrafts[aircraft.flightNumber] = aircraft;
  }
  
  @override
  void sendMessage(String message, String sender) {
    print('Control Tower: $message from $sender');
  }
  
  void grantTakeoff(String flightNumber) {
    print('Control Tower: Takeoff granted to $flightNumber');
    final aircraft = _aircrafts[flightNumber];
    if (aircraft != null) {
      aircraft.setAltitude(10000);
    }
  }
  
  void grantLanding(String flightNumber) {
    print('Control Tower: Landing granted to $flightNumber');
    final aircraft = _aircrafts[flightNumber];
    if (aircraft != null) {
      aircraft.setAltitude(0);
    }
  }
}
