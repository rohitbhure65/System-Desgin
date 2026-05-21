import 'interfaces.dart';
import 'chat_room.dart';
import 'air_traffic_control.dart';
import 'smart_home.dart';

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
