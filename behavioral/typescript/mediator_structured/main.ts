import { User, Bot, ChatRoom } from './chat_room';
import { Aircraft, ControlTower } from './air_traffic_control';
import { SmartLight, SmartThermostat, HomeHub } from './smart_home';

console.log('=== Mediator Pattern Demo ===\n');

// Example 1: Chat Room
console.log('--- Chat Room Example ---');

const chatRoom = new ChatRoom();

const user1 = new User(chatRoom, 'Alice');
const user2 = new User(chatRoom, 'Bob');
const bot = new Bot(chatRoom, 'HelperBot');

chatRoom.addUser(user1);
chatRoom.addUser(user2);
chatRoom.addUser(bot);

console.log('\nAlice sends a message:');
user1.send('Hello everyone!');

console.log('\nBob sends a message:');
user2.send('Hi Alice!');

console.log('');

// Example 2: Air Traffic Control
console.log('--- Air Traffic Control Example ---');

const controlTower = new ControlTower();

const flight1 = new Aircraft(controlTower, 'AA123');
const flight2 = new Aircraft(controlTower, 'UA456');

controlTower.registerAircraft(flight1);
controlTower.registerAircraft(flight2);

console.log('\nFlight AA123 requests takeoff:');
controlTower.grantTakeoff('AA123');

console.log('\nFlight UA456 requests landing:');
controlTower.grantLanding('UA456');

console.log('');

// Example 3: Smart Home System
console.log('--- Smart Home System Example ---');

const homeHub = new HomeHub();

const livingRoomLight = new SmartLight(homeHub, 'Living Room Light');
const bedroomLight = new SmartLight(homeHub, 'Bedroom Light');
const thermostat = new SmartThermostat(homeHub, 'Main Thermostat');

homeHub.addDevice(livingRoomLight);
homeHub.addDevice(bedroomLight);
homeHub.addDevice(thermostat);

console.log('\nTurning on thermostat (should trigger lights):');
thermostat.turnOn();

console.log('\nActivating away mode:');
homeHub.activateAwayMode();

console.log('\nActivating home mode:');
homeHub.activateHomeMode();
