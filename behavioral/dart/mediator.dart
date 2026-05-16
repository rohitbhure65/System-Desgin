/*
 * MEDIATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Mediator pattern defines an object that encapsulates how a set of objects interact.
 * It promotes loose coupling by preventing objects from referring to each other explicitly.
 * 
 * WHY DOES IT EXIST?
 * - When you want to reduce the chaotic dependencies between objects
 * - When you want to centralize complex communications and control logic between related objects
 * - When you want to reuse the interaction logic without duplicating it across multiple objects
 * 
 * WHEN TO USE IT?
 * - When a set of objects communicate in well-defined but complex ways
 * - When you want to customize a behavior that's distributed between several objects without subclassing
 * - When you have many objects that need to interact with each other
 * - Common use cases: chat rooms, air traffic control, GUI frameworks, auction systems
 * 
 * PROS:
 * - Single Responsibility Principle (extracts communication logic to a separate class)
 * - Open/Closed Principle (can add new colleagues without changing the mediator)
 * - Reduces coupling between colleagues
 * - Simplifies object interactions
 * 
 * CONS:
 * - The mediator can become a monolith (god object) if not carefully designed
 * - Can make the system harder to understand due to indirect communication
 * - May reduce performance due to indirection
 * - Can be overkill for simple interactions
 * 
 * REAL-WORLD ANALOGY:
 * Think of an air traffic control tower. Planes (colleagues) don't communicate directly with each other - they all communicate through the tower (mediator). The tower coordinates takeoffs, landings, and routes, ensuring planes don't collide. This centralizes the coordination logic and prevents planes from needing to know about each other.
 */

// Mediator interface - declares the communication interface
abstract class Mediator {
  void sendMessage(String message, String sender);
}

// Colleague interface - declares the interface for communicating with the mediator
abstract class Colleague {
  final Mediator _mediator;
  final String _name;
  
  Colleague(this._mediator, this._name);
  
  void send(String message) {
    _mediator.sendMessage(message, _name);
  }
  
  void receive(String message);
  
  String get name => _name;
}

// Concrete Colleague 1
class User extends Colleague {
  User(super.mediator, super.name);
  
  @override
  void receive(String message) {
    print('$_name received: $message');
  }
}

// Concrete Colleague 2
class Bot extends Colleague {
  Bot(super.mediator, super.name);
  
  @override
  void receive(String message) {
    print('$_name received: $message');
    // Bot can auto-reply
    send('Auto-reply: Thanks for your message!');
  }
}

// Concrete Mediator
class ChatRoom implements Mediator {
  final Map<String, Colleague> _colleagues = {};
  
  void addUser(Colleague colleague) {
    _colleagues[colleague.name] = colleague;
  }
  
  @override
  void sendMessage(String message, String sender) {
    print('$sender sends: $message');
    for (final entry in _colleagues.entries) {
      if (entry.key != sender) {
        entry.value.receive(message);
      }
    }
  }
}

// Example 2: Air Traffic Control
// Shows how Mediator can coordinate complex interactions

class Aircraft {
  final String _flightNumber;
  int _altitude = 0;
  
  Aircraft(this._flightNumber);
  
  void requestTakeoff() {
    print('$_flightNumber requesting takeoff clearance...');
    // In real implementation, would send to mediator
  }
  
  void requestLanding() {
    print('$_flightNumber requesting landing clearance...');
    // In real implementation, would send to mediator
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
    // Simplified for demo
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

// Example 3: Smart Home System
// Shows how Mediator can coordinate home automation

class SmartDevice {
  final Mediator _homeHub;
  final String _deviceName;
  bool _isOn = false;
  
  SmartDevice(this._homeHub, this._deviceName);
  
  void turnOn() {
    _isOn = true;
    print('$_deviceName turned ON');
    _homeHub.sendMessage('$_deviceName turned ON', _deviceName);
  }
  
  void turnOff() {
    _isOn = false;
    print('$_deviceName turned OFF');
    _homeHub.sendMessage('$_deviceName turned OFF', _deviceName);
  }
  
  String get name => _deviceName;
  
  bool get isOn => _isOn;
}

class SmartLight extends SmartDevice {
  SmartLight(super.homeHub, super.name);
}

class SmartThermostat extends SmartDevice {
  int _temperature = 70;
  
  SmartThermostat(super.homeHub, super.name);
  
  void setTemperature(int temp) {
    _temperature = temp;
    print('$name set to $_temperature°F');
  }
  
  int get temperature => _temperature;
}

class HomeHub implements Mediator {
  final Map<String, SmartDevice> _devices = {};
  
  void addDevice(SmartDevice device) {
    _devices[device.name] = device;
  }
  
  @override
  void sendMessage(String message, String sender) {
    print('Home Hub: $message');
    
    // Example logic: if thermostat turns on, turn on lights
    if (sender.contains('Thermostat') && message.contains('turned ON')) {
      for (final device in _devices.values) {
        if (device.name.contains('Light') && !device.isOn) {
          device.turnOn();
        }
      }
    }
  }
  
  void activateAwayMode() {
    print('Home Hub: Activating away mode...');
    for (final device in _devices.values) {
      if (device.isOn) {
        device.turnOff();
      }
    }
  }
  
  void activateHomeMode() {
    print('Home Hub: Activating home mode...');
    for (final device in _devices.values) {
      if (device.name.contains('Light')) {
        device.turnOn();
      }
    }
  }
}

// Demo code
void main() {
  print('=== Mediator Pattern Demo ===\n');
  
  // Example 1: Chat Room
  print('--- Chat Room Example ---');
  
  final chatRoom = ChatRoom();
  
  final user1 = User(chatRoom, 'Alice');
  final user2 = User(chatRoom, 'Bob');
  final bot = Bot(chatRoom, 'HelperBot');
  
  chatRoom.addUser(user1);
  chatRoom.addUser(user2);
  chatRoom.addUser(bot);
  
  print('\nAlice sends a message:');
  user1.send('Hello everyone!');
  
  print('\nBob sends a message:');
  user2.send('Hi Alice!');
  
  print('');
  
  // Example 2: Air Traffic Control
  print('--- Air Traffic Control Example ---');
  
  final controlTower = ControlTower();
  
  final flight1 = Aircraft('AA123');
  final flight2 = Aircraft('UA456');
  
  controlTower.registerAircraft(flight1);
  controlTower.registerAircraft(flight2);
  
  print('\nFlight AA123 requests takeoff:');
  controlTower.grantTakeoff('AA123');
  
  print('\nFlight UA456 requests landing:');
  controlTower.grantLanding('UA456');
  
  print('');
  
  // Example 3: Smart Home System
  print('--- Smart Home System Example ---');
  
  final homeHub = HomeHub();
  
  final livingRoomLight = SmartLight(homeHub, 'Living Room Light');
  final bedroomLight = SmartLight(homeHub, 'Bedroom Light');
  final thermostat = SmartThermostat(homeHub, 'Main Thermostat');
  
  homeHub.addDevice(livingRoomLight);
  homeHub.addDevice(bedroomLight);
  homeHub.addDevice(thermostat);
  
  print('\nTurning on thermostat (should trigger lights):');
  thermostat.turnOn();
  
  print('\nActivating away mode:');
  homeHub.activateAwayMode();
  
  print('\nActivating home mode:');
  homeHub.activateHomeMode();
}
