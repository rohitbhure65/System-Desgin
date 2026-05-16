/*
 * FACADE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Facade pattern provides a simplified interface to a library, a framework, or any other complex set of classes.
 * It hides the complexities of the larger system and provides a simpler interface to the client.
 * 
 * WHY DOES IT EXIST?
 * - When you need to provide a simple interface to a complex subsystem
 * - When you want to reduce dependencies between clients and the implementation of an abstraction
 * - When you want to layer your subsystems (use facade to define entry points)
 * 
 * WHEN TO USE IT?
 * - When you have a complex system with many interacting classes
 * - When you want to provide a simple interface for clients to interact with the system
 * - When you want to decouple the client from the subsystem implementation
 * - Common use cases: API libraries, database operations, complex UI systems, payment processing
 * 
 * PROS:
 * - Simplifies the interface to a complex subsystem
 * - Decouples clients from the subsystem (reduces coupling)
 * - Makes the system easier to use and understand
 * - Promotes loose coupling between subsystems and clients
 * 
 * CONS:
 * - Can become a "god object" if not carefully designed
 * - May limit the flexibility of the subsystem
 * - Can hide useful functionality from advanced users
 * - Adds an extra layer of indirection
 * 
 * REAL-WORLD ANALOGY:
 * Think of a car dashboard. The dashboard (facade) provides a simple interface to the complex car systems (engine, transmission, brakes, etc.). You don't need to know how the engine works to drive the car - you just use the steering wheel, pedals, and dashboard controls. The dashboard hides the complexity while giving you access to the essential functions.
 */

// Subsystem Class 1: CPU
class CPU {
  freeze(): void {
    console.log('CPU: Freezing...');
  }
  
  jump(position: number): void {
    console.log(`CPU: Jumping to position ${position}`);
  }
  
  execute(): void {
    console.log('CPU: Executing instructions...');
  }
}

// Subsystem Class 2: Memory
class Memory {
  load(position: number, data: string): void {
    console.log(`Memory: Loading data '${data}' at position ${position}`);
  }
}

// Subsystem Class 3: Hard Drive
class HardDrive {
  read(lba: number, size: number): string {
    console.log(`HardDrive: Reading ${size} bytes from LBA ${lba}`);
    return 'Boot Data';
  }
}

// Facade - provides a simplified interface to the complex subsystem
class ComputerFacade {
  private cpu: CPU;
  private memory: Memory;
  private hardDrive: HardDrive;
  
  constructor() {
    this.cpu = new CPU();
    this.memory = new Memory();
    this.hardDrive = new HardDrive();
  }
  
  start(): void {
    console.log('=== Starting Computer ===');
    this.cpu.freeze();
    this.memory.load(0, this.hardDrive.read(0, 1024));
    this.cpu.jump(0);
    this.cpu.execute();
    console.log('=== Computer Started ===');
  }
  
  shutdown(): void {
    console.log('=== Shutting Down Computer ===');
    console.log('CPU: Stopping...');
    console.log('Memory: Clearing...');
    console.log('HardDrive: Spinning down...');
    console.log('=== Computer Shutdown ===');
  }
}

// Example 2: Home Theater System
// Shows how Facade can simplify controlling multiple devices

class Amplifier {
  on(): void { console.log('Amplifier: ON'); }
  off(): void { console.log('Amplifier: OFF'); }
  setVolume(level: number): void { console.log(`Amplifier: Volume set to ${level}`); }
}

class Tuner {
  on(): void { console.log('Tuner: ON'); }
  off(): void { console.log('Tuner: OFF'); }
  setFrequency(freq: number): void { console.log(`Tuner: Frequency set to ${freq} FM`); }
}

class DVDPlayer {
  on(): void { console.log('DVD Player: ON'); }
  off(): void { console.log('DVD Player: OFF'); }
  play(movie: string): void { console.log(`DVD Player: Playing '${movie}'`); }
}

class Projector {
  on(): void { console.log('Projector: ON'); }
  off(): void { console.log('Projector: OFF'); }
  setInput(input: string): void { console.log(`Projector: Input set to ${input}`); }
}

class TheaterLights {
  on(): void { console.log('Theater Lights: ON'); }
  off(): void { console.log('Theater Lights: OFF'); }
  dim(level: number): void { console.log(`Theater Lights: Dimmed to ${level}%`); }
}

class Screen {
  up(): void { console.log('Screen: UP'); }
  down(): void { console.log('Screen: DOWN'); }
}

class PopcornPopper {
  on(): void { console.log('Popcorn Popper: ON'); }
  off(): void { console.log('Popcorn Popper: OFF'); }
  pop(): void { console.log('Popcorn Popper: Popping popcorn!'); }
}

// Facade for Home Theater
class HomeTheaterFacade {
  private amp: Amplifier;
  private tuner: Tuner;
  private dvd: DVDPlayer;
  private projector: Projector;
  private lights: TheaterLights;
  private screen: Screen;
  private popper: PopcornPopper;
  
  constructor() {
    this.amp = new Amplifier();
    this.tuner = new Tuner();
    this.dvd = new DVDPlayer();
    this.projector = new Projector();
    this.lights = new TheaterLights();
    this.screen = new Screen();
    this.popper = new PopcornPopper();
  }
  
  watchMovie(movie: string): void {
    console.log('\n=== Get ready to watch a movie ===');
    this.popper.on();
    this.popper.pop();
    this.lights.dim(10);
    this.screen.down();
    this.projector.on();
    this.projector.setInput('DVD');
    this.amp.on();
    this.amp.setVolume(5);
    this.dvd.on();
    this.dvd.play(movie);
    console.log('=== Movie is playing ===');
  }
  
  endMovie(): void {
    console.log('\n=== Shutting movie theater down ===');
    this.popper.off();
    this.lights.on();
    this.screen.up();
    this.projector.off();
    this.amp.off();
    this.dvd.off();
    console.log('=== Movie theater shut down ===');
  }
  
  listenToRadio(frequency: number): void {
    console.log('\n=== Tuning in to radio ===');
    this.amp.on();
    this.amp.setVolume(5);
    this.tuner.on();
    this.tuner.setFrequency(frequency);
    console.log('=== Radio is playing ===');
  }
  
  turnOffRadio(): void {
    console.log('\n=== Shutting down radio ===');
    this.tuner.off();
    this.amp.off();
    console.log('=== Radio turned off ===');
  }
}

// Example 3: Order Processing System
// Shows how Facade can simplify complex business logic

class InventorySystem {
  checkInventory(item: string, quantity: number): boolean {
    console.log(`Inventory: Checking ${quantity} units of ${item}`);
    return true;  // Simplified for demo
  }
  
  updateInventory(item: string, quantity: number): void {
    console.log(`Inventory: Updating ${quantity} units of ${item}`);
  }
}

class PaymentSystem {
  processPayment(amount: number): boolean {
    console.log(`Payment: Processing payment of $${amount}`);
    return true;  // Simplified for demo
  }
  
  refundPayment(amount: number): void {
    console.log(`Payment: Refunding $${amount}`);
  }
}

class ShippingSystem {
  scheduleShipping(address: string): void {
    console.log(`Shipping: Scheduling delivery to ${address}`);
  }
  
  cancelShipping(): void {
    console.log('Shipping: Cancelling delivery');
  }
}

class NotificationSystem {
  sendConfirmation(email: string): void {
    console.log(`Notification: Sending confirmation to ${email}`);
  }
  
  sendCancellation(email: string): void {
    console.log(`Notification: Sending cancellation to ${email}`);
  }
}

// Facade for Order Processing
class OrderFacade {
  private inventory: InventorySystem;
  private payment: PaymentSystem;
  private shipping: ShippingSystem;
  private notification: NotificationSystem;
  
  constructor() {
    this.inventory = new InventorySystem();
    this.payment = new PaymentSystem();
    this.shipping = new ShippingSystem();
    this.notification = new NotificationSystem();
  }
  
  placeOrder(item: string, quantity: number, amount: number, 
             address: string, email: string): boolean {
    console.log('\n=== Processing Order ===');
    
    if (!this.inventory.checkInventory(item, quantity)) {
      console.log('Order failed: Item not in stock');
      return false;
    }
    
    if (!this.payment.processPayment(amount)) {
      console.log('Order failed: Payment declined');
      return false;
    }
    
    this.inventory.updateInventory(item, -quantity);
    this.shipping.scheduleShipping(address);
    this.notification.sendConfirmation(email);
    
    console.log('=== Order Placed Successfully ===');
    return true;
  }
  
  cancelOrder(item: string, quantity: number, amount: number,
              email: string): void {
    console.log('\n=== Cancelling Order ===');
    this.inventory.updateInventory(item, quantity);
    this.payment.refundPayment(amount);
    this.shipping.cancelShipping();
    this.notification.sendCancellation(email);
    console.log('=== Order Cancelled ===');
  }
}

// Demo code
function demoFacade(): void {
  console.log('=== Facade Pattern Demo ===\n');
  
  // Example 1: Computer Boot
  console.log('--- Computer Boot Example ---');
  
  const computer = new ComputerFacade();
  computer.start();
  console.log();
  computer.shutdown();
  
  console.log();
  
  // Example 2: Home Theater
  console.log('--- Home Theater Example ---');
  
  const homeTheater = new HomeTheaterFacade();
  homeTheater.watchMovie('The Matrix');
  homeTheater.endMovie();
  homeTheater.listenToRadio(98.7);
  homeTheater.turnOffRadio();
  
  console.log();
  
  // Example 3: Order Processing
  console.log('--- Order Processing Example ---');
  
  const orderSystem = new OrderFacade();
  orderSystem.placeOrder('Laptop', 1, 999.99, '123 Main St', 'customer@email.com');
  orderSystem.cancelOrder('Laptop', 1, 999.99, 'customer@email.com');
}

// Run the demo
demoFacade();
