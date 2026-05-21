class CPU {
  void freeze() { print('CPU: Freezing...'); }
  void jump(int position) { print('CPU: Jumping to position \$position'); }
  void execute() { print('CPU: Executing instructions...'); }
}

class Memory {
  void load(int position, String data) { print('Memory: Loading data \\'\$data\\' at position \$position'); }
}

class HardDrive {
  String read(int lba, int size) {
    print('HardDrive: Reading \$size bytes from LBA \$lba');
    return 'Boot Data';
  }
}

class Amplifier {
  void on() => print('Amplifier: ON');
  void off() => print('Amplifier: OFF');
  void setVolume(int level) => print('Amplifier: Volume set to \$level');
}

class Tuner {
  void on() => print('Tuner: ON');
  void off() => print('Tuner: OFF');
  void setFrequency(double freq) => print('Tuner: Frequency set to \$freq FM');
}

class DVDPlayer {
  void on() => print('DVD Player: ON');
  void off() => print('DVD Player: OFF');
  void play(String movie) => print('DVD Player: Playing \\'\$movie\\'');
}

class Projector {
  void on() => print('Projector: ON');
  void off() => print('Projector: OFF');
  void setInput(String input) => print('Projector: Input set to \$input');
}

class TheaterLights {
  void on() => print('Theater Lights: ON');
  void off() => print('Theater Lights: OFF');
  void dim(int level) => print('Theater Lights: Dimmed to \$level%');
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

class InventorySystem {
  bool checkInventory(String item, int quantity) {
    print('Inventory: Checking \$quantity units of \$item');
    return true;
  }
  void updateInventory(String item, int quantity) {
    print('Inventory: Updating \$quantity units of \$item');
  }
}

class PaymentSystem {
  bool processPayment(double amount) {
    print('Payment: Processing payment of \$\amount');
    return true;
  }
  void refundPayment(double amount) {
    print('Payment: Refunding \$\amount');
  }
}

class ShippingSystem {
  void scheduleShipping(String address) { print('Shipping: Scheduling delivery to \$address'); }
  void cancelShipping() { print('Shipping: Cancelling delivery'); }
}

class NotificationSystem {
  void sendConfirmation(String email) { print('Notification: Sending confirmation to \$email'); }
  void sendCancellation(String email) { print('Notification: Sending cancellation to \$email'); }
}
