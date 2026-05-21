import 'subsystems.dart';

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
    _popper.on(); _popper.pop();
    _lights.dim(10);
    _screen.down();
    _projector.on(); _projector.setInput('DVD');
    _amp.on(); _amp.setVolume(5);
    _dvd.on(); _dvd.play(movie);
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
    _amp.on(); _amp.setVolume(5);
    _tuner.on(); _tuner.setFrequency(frequency);
    print('=== Radio is playing ===');
  }
  
  void turnOffRadio() {
    print('\n=== Shutting down radio ===');
    _tuner.off();
    _amp.off();
    print('=== Radio turned off ===');
  }
}

class OrderFacade {
  final InventorySystem _inventory = InventorySystem();
  final PaymentSystem _payment = PaymentSystem();
  final ShippingSystem _shipping = ShippingSystem();
  final NotificationSystem _notification = NotificationSystem();
  
  bool placeOrder(String item, int quantity, double amount, String address, String email) {
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
