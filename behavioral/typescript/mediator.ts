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
interface Mediator {
  sendMessage(message: string, sender: string): void;
}

// Colleague interface - declares the interface for communicating with the mediator
abstract class Colleague {
  protected mediator: Mediator;
  protected name: string;
  
  constructor(mediator: Mediator, name: string) {
    this.mediator = mediator;
    this.name = name;
  }
  
  send(message: string): void {
    this.mediator.sendMessage(message, this.name);
  }
  
  abstract receive(message: string): void;
  
  getName(): string {
    return this.name;
  }
}

// Concrete Colleague 1
class User extends Colleague {
  constructor(mediator: Mediator, name: string) {
    super(mediator, name);
  }
  
  receive(message: string): void {
    console.log(`${this.name} received: ${message}`);
  }
}

// Concrete Colleague 2
class Bot extends Colleague {
  constructor(mediator: Mediator, name: string) {
    super(mediator, name);
  }
  
  receive(message: string): void {
    console.log(`${this.name} received: ${message}`);
    // Bot can auto-reply
    this.send('Auto-reply: Thanks for your message!');
  }
}

// Concrete Mediator
class ChatRoom implements Mediator {
  private colleagues: Map<string, Colleague> = new Map();
  
  addUser(colleague: Colleague): void {
    this.colleagues.set(colleague.getName(), colleague);
  }
  
  sendMessage(message: string, sender: string): void {
    console.log(`${sender} sends: ${message}`);
    for (const [name, colleague] of this.colleagues) {
      if (name !== sender) {
        colleague.receive(message);
      }
    }
  }
}

// Example 2: Air Traffic Control
// Shows how Mediator can coordinate complex interactions

class Aircraft {
  protected controlTower: Mediator;
  protected flightNumber: string;
  protected altitude: number = 0;
  protected speed: number = 0;
  
  constructor(tower: Mediator, flightNumber: string) {
    this.controlTower = tower;
    this.flightNumber = flightNumber;
  }
  
  requestTakeoff(): void {
    console.log(`${this.flightNumber} requesting takeoff clearance...`);
    // In real implementation, would send to mediator
  }
  
  requestLanding(): void {
    console.log(`${this.flightNumber} requesting landing clearance...`);
    // In real implementation, would send to mediator
  }
  
  setAltitude(alt: number): void {
    this.altitude = alt;
    console.log(`${this.flightNumber} at altitude ${this.altitude} feet`);
  }
  
  getFlightNumber(): string {
    return this.flightNumber;
  }
}

class ControlTower implements Mediator {
  private aircrafts: Map<string, Aircraft> = new Map();
  
  registerAircraft(aircraft: Aircraft): void {
    this.aircrafts.set(aircraft.getFlightNumber(), aircraft);
  }
  
  sendMessage(message: string, sender: string): void {
    // Simplified for demo
    console.log(`Control Tower: ${message} from ${sender}`);
  }
  
  grantTakeoff(flightNumber: string): void {
    console.log(`Control Tower: Takeoff granted to ${flightNumber}`);
    const aircraft = this.aircrafts.get(flightNumber);
    if (aircraft) {
      aircraft.setAltitude(10000);
    }
  }
  
  grantLanding(flightNumber: string): void {
    console.log(`Control Tower: Landing granted to ${flightNumber}`);
    const aircraft = this.aircrafts.get(flightNumber);
    if (aircraft) {
      aircraft.setAltitude(0);
    }
  }
}

// Example 3: Smart Home System
// Shows how Mediator can coordinate home automation

class SmartDevice {
  protected homeHub: Mediator;
  protected deviceName: string;
  protected isOn: boolean = false;
  
  constructor(hub: Mediator, name: string) {
    this.homeHub = hub;
    this.deviceName = name;
  }
  
  turnOn(): void {
    this.isOn = true;
    console.log(`${this.deviceName} turned ON`);
    this.homeHub.sendMessage(`${this.deviceName} turned ON`, this.deviceName);
  }
  
  turnOff(): void {
    this.isOn = false;
    console.log(`${this.deviceName} turned OFF`);
    this.homeHub.sendMessage(`${this.deviceName} turned OFF`, this.deviceName);
  }
  
  getName(): string {
    return this.deviceName;
  }
  
  getStatus(): boolean {
    return this.isOn;
  }
}

class SmartLight extends SmartDevice {
  constructor(hub: Mediator, name: string) {
    super(hub, name);
  }
}

class SmartThermostat extends SmartDevice {
  private temperature: number = 70;
  
  constructor(hub: Mediator, name: string) {
    super(hub, name);
  }
  
  setTemperature(temp: number): void {
    this.temperature = temp;
    console.log(`${this.getName()} set to ${this.temperature}°F`);
  }
  
  getTemperature(): number {
    return this.temperature;
  }
}

class HomeHub implements Mediator {
  private devices: Map<string, SmartDevice> = new Map();
  
  addDevice(device: SmartDevice): void {
    this.devices.set(device.getName(), device);
  }
  
  sendMessage(message: string, sender: string): void {
    console.log(`Home Hub: ${message}`);
    
    // Example logic: if thermostat turns on, turn on lights
    if (sender.includes('Thermostat') && message.includes('turned ON')) {
      for (const [name, device] of this.devices) {
        if (name.includes('Light') && !device.getStatus()) {
          device.turnOn();
        }
      }
    }
  }
  
  activateAwayMode(): void {
    console.log('Home Hub: Activating away mode...');
    for (const [name, device] of this.devices) {
      if (device.getStatus()) {
        device.turnOff();
      }
    }
  }
  
  activateHomeMode(): void {
    console.log('Home Hub: Activating home mode...');
    for (const [name, device] of this.devices) {
      if (name.includes('Light')) {
        device.turnOn();
      }
    }
  }
}

// Demo code
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
