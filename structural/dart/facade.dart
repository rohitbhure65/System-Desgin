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
  void freeze() {
    print('CPU: Freezing...');
  }
  
  void jump(int position) {
    print('CPU: Jumping to position $position');
  }
  
  void execute() {
    print('CPU: Executing instructions...');
  }
}

// Subsystem Class 2: Memory
class Memory {
  void load(int position, String data) {
    print('Memory: Loading data \'$data\' at position $position');
  }
}

// Subsystem Class 3: Hard Drive
class HardDrive {
  String read(int lba, int size) {
    print('HardDrive: Reading $size bytes from LBA $lba');
    return 'Boot Data';
  }
}

// Facade - provides a simplified interface to the complex subsystem
class ComputerFacade {
  final CPU _cpu = CPU();
  final Memory _memory = Memory();
  final HardDrive _hardDrive = HardDrive();
  
  void start() {
    print('=== Starting Computer ===');
    _cpu.freeze();
    _memory.load(0, _hardDrive.read(0, 1024));
    _cpu.jump(0);
    _cpu.execute();
    print('=== Computer Started ===');
  }
  
  void shutdown() {
    print('=== Shutting Down Computer ===');
    print('CPU: Stopping...');
    print('Memory: Clearing...');
    print('HardDrive: Spinning down...');
    print('=== Computer Shutdown ===');
  }
}

// Example 2: Home Theater System
// Shows how Facade can simplify controlling multiple devices

class Amplifier {
  void on() => print('Amplifier: ON');
  void off() => print('Amplifier: OFF');
  void setVolume(int level) => print('Amplifier: Volume set to $level');
}

class Tuner {
  void on() => print('Tuner: ON');
  void off() => print('Tuner: OFF');
  void setFrequency(double freq) => print('Tuner: Frequency set to $freq FM');
}

class DVDPlayer {
  void on() => print('DVD Player: ON');
  void off() => print('DVD Player: OFF');
  void play(String movie) => print('DVD Player: Playing \'$movie\'');
}

class Projector {
  void on() => print('Projector: ON');
  void off() => print('Projector: OFF');
  void setInput(String input) => print('Projector: Input set to $input');
}

class TheaterLights {
  void on() => print('Theater Lights: ON');
  void off() => print('Theater Lights: OFF');
  void dim(int level) => print('Theater Lights: Dimmed to $level%');
}

class ProjectionScreen {
  void down() => print('Screen: DOWN');
  void up() => print('Screen: UP');
}

class PopcornPopper {
  void on() => print('Popcorn Popper: ON');
  void off() => print('Popcorn Popper: OFF');
  void pop() => print('Popcorn Popper: Popping popcorn!');
}

// Facade for Home Theater
class HomeTheaterFacade {
  final Amplifier _amp = Amplifier();
  final Tuner _tuner = Tuner();
  final DVDPlayer _dvd = DVDPlayer();
  final Projector _projector = Projector();
  final TheaterLights _lights = TheaterLights();
  final ProjectionScreen _screen = ProjectionScreen();
  final PopcornPopper _popper = PopcornPopper();
  
  void watchMovie(String movie) {
    print('\n=== Get ready to watch a movie ===');
    _popper.on();
    _popper.pop();
    _lights.dim(10);
    _screen.down();
    _projector.on();
    _projector.setInput('DVD');
    _amp.on();
    _amp.setVolume(5);
    _dvd.on();
    _dvd.play(movie);
    print('=== Movie is playing ===');
  }
  
  void endMovie() {
    print('\n=== Shutting movie theater down ===');
    _popper.off();
    _lights.on();
    _screen.up();
    _projector.off();
    _amp.off();
    _dvd.off();
    print('=== Movie theater shut down ===');
  }
  
  void listenToRadio(double frequency) {
    print('\n=== Tuning in to radio ===');
    _amp.on();
    _amp.setVolume(5);
    _tuner.on();
    _tuner.setFrequency(frequency);
    print('=== Radio is playing ===');
  }
  
  void turnOffRadio() {
    print('\n=== Shutting down radio ===');
    _tuner.off();
    _amp.off();
    print('=== Radio turned off ===');
  }
}

// Example 3: Order Processing System
// Shows how Facade can simplify complex business logic

class InventorySystem {
  bool checkInventory(String item, int quantity) {
    print('Inventory: Checking $quantity units of $item');
    return true;  // Simplified for demo
  }
  
  void updateInventory(String item, int quantity) {
    print('Inventory: Updating $quantity units of $item');
  }
}

class PaymentSystem {
  bool processPayment(double amount) {
    print('Payment: Processing payment of \$$amount');
    return true;  // Simplified for demo
  }
  
  void refundPayment(double amount) {
    print('Payment: Refunding \$$amount');
  }
}

class ShippingSystem {
  void scheduleShipping(String address) {
    print('Shipping: Scheduling delivery to $address');
  }
  
  void cancelShipping() {
    print('Shipping: Cancelling delivery');
  }
}

class NotificationSystem {
  void sendConfirmation(String email) {
    print('Notification: Sending confirmation to $email');
  }
  
  void sendCancellation(String email) {
    print('Notification: Sending cancellation to $email');
  }
}

// Facade for Order Processing
class OrderFacade {
  final InventorySystem _inventory = InventorySystem();
  final PaymentSystem _payment = PaymentSystem();
  final ShippingSystem _shipping = ShippingSystem();
  final NotificationSystem _notification = NotificationSystem();
  
  bool placeOrder(String item, int quantity, double amount, 
                  String address, String email) {
    print('\n=== Processing Order ===');
    
    if (!_inventory.checkInventory(item, quantity)) {
      print('Order failed: Item not in stock');
      return false;
    }
    
    if (!_payment.processPayment(amount)) {
      print('Order failed: Payment declined');
      return false;
    }
    
    _inventory.updateInventory(item, -quantity);
    _shipping.scheduleShipping(address);
    _notification.sendConfirmation(email);
    
    print('=== Order Placed Successfully ===');
    return true;
  }
  
  void cancelOrder(String item, int quantity, double amount, String email) {
    print('\n=== Cancelling Order ===');
    _inventory.updateInventory(item, quantity);
    _payment.refundPayment(amount);
    _shipping.cancelShipping();
    _notification.sendCancellation(email);
    print('=== Order Cancelled ===');
  }
}

// Demo code
void main() {
  print('=== Facade Pattern Demo ===\n');
  
  // Example 1: Computer Boot
  print('--- Computer Boot Example ---');
  
  var computer = ComputerFacade();
  computer.start();
  print('');
  computer.shutdown();
  
  print('');
  
  // Example 2: Home Theater
  print('--- Home Theater Example ---');
  
  var homeTheater = HomeTheaterFacade();
  homeTheater.watchMovie('The Matrix');
  homeTheater.endMovie();
  homeTheater.listenToRadio(98.7);
  homeTheater.turnOffRadio();
  
  print('');
  
  // Example 3: Order Processing
  print('--- Order Processing Example ---');
  
  var orderSystem = OrderFacade();
  orderSystem.placeOrder('Laptop', 1, 999.99, '123 Main St', 'customer@email.com');
  orderSystem.cancelOrder('Laptop', 1, 999.99, 'customer@email.com');
}
