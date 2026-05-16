/*
 * COMMAND DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Command pattern turns a request into a stand-alone object that contains all information about the request.
 * It lets you parameterize clients with different requests, queue or log requests, and support undoable operations.
 * 
 * WHY DOES IT EXIST?
 * - When you want to parameterize objects with operations
 * - When you want to queue operations, schedule their execution, or execute them remotely
 * - When you need to support undo operations
 * - When you want to decouple the object that invokes an operation from the one that knows how to perform it
 * 
 * WHEN TO USE IT?
 * - When you want to parameterize objects with an operation to execute
 * - When you want to queue operations, schedule their execution, or execute them remotely
 * - When you need to support undo/redo functionality
 * - When you want to decouple the invoker from the receiver
 * - Common use cases: GUI buttons and menus, multi-level undo, macro recording, transactional systems
 * 
 * PROS:
 * - Decouples the object that invokes the operation from the one that knows how to perform it
 * - Can add new commands without changing existing code (Open/Closed Principle)
 * - Allows you to assemble commands into more complex commands (composite pattern)
 * - Supports undo/redo operations
 * 
 * CONS:
 * - Can lead to many small command classes (code complexity)
 * - Can complicate the code if the receiver and command are tightly coupled
 * - May introduce additional layers of indirection
 * - Can make debugging more difficult
 * 
 * REAL-WORLD ANALOGY:
 * Think of a restaurant order. The customer (client) places an order (command) with the waiter (invoker). The waiter writes down the order and gives it to the kitchen (receiver). The kitchen executes the command (prepares the meal). The order can be cancelled (undo) before it's prepared, and multiple orders can be queued.
 */

// Receiver - knows how to perform the operations
class Light {
  void on() {
    print('Light is ON');
  }
  
  void off() {
    print('Light is OFF');
  }
}

class Stereo {
  void on() {
    print('Stereo is ON');
  }
  
  void off() {
    print('Stereo is OFF');
  }
  
  void setVolume(int level) {
    print('Stereo volume set to $level');
  }
}

// Command interface - declares the execute method
abstract class Command {
  void execute();
  void undo();
}

// Concrete Command 1: Light On
class LightOnCommand extends Command {
  final Light _light;
  
  LightOnCommand(this._light);
  
  @override
  void execute() {
    _light.on();
  }
  
  @override
  void undo() {
    _light.off();
  }
}

// Concrete Command 2: Light Off
class LightOffCommand extends Command {
  final Light _light;
  
  LightOffCommand(this._light);
  
  @override
  void execute() {
    _light.off();
  }
  
  @override
  void undo() {
    _light.on();
  }
}

// Concrete Command 3: Stereo On with Volume
class StereoOnCommand extends Command {
  final Stereo _stereo;
  int _previousVolume = 0;
  
  StereoOnCommand(this._stereo);
  
  @override
  void execute() {
    _stereo.on();
    _stereo.setVolume(10);
    _previousVolume = 10;
  }
  
  @override
  void undo() {
    _stereo.setVolume(_previousVolume);
    _stereo.off();
  }
}

// Concrete Command 4: Stereo Off
class StereoOffCommand extends Command {
  final Stereo _stereo;
  
  StereoOffCommand(this._stereo);
  
  @override
  void execute() {
    _stereo.off();
  }
  
  @override
  void undo() {
    _stereo.on();
  }
}

// Invoker - asks the command to carry out the request
class RemoteControl {
  final List<Command> _commandHistory = [];
  final List<Command> _undoStack = [];
  
  void setCommand(Command command) {
    _commandHistory.add(command);
  }
  
  void buttonPressed(int slot) {
    if (slot < _commandHistory.length) {
      _commandHistory[slot].execute();
      _undoStack.add(_commandHistory[slot]);
    }
  }
  
  void undoButtonPressed() {
    if (_undoStack.isNotEmpty) {
      final command = _undoStack.removeLast();
      command.undo();
    } else {
      print('Nothing to undo');
    }
  }
}

// Example 2: Macro Command
// Shows how multiple commands can be combined into one

class MacroCommand extends Command {
  final List<Command> _commands = [];
  
  void addCommand(Command command) {
    _commands.add(command);
  }
  
  @override
  void execute() {
    for (final command in _commands) {
      command.execute();
    }
  }
  
  @override
  void undo() {
    // Undo in reverse order
    for (int i = _commands.length - 1; i >= 0; i--) {
      _commands[i].undo();
    }
  }
}

// Example 3: Transaction Command
// Shows how Command can be used for transactional operations

class BankAccount {
  double _balance = 0;
  
  BankAccount([double initialBalance = 0]) : _balance = initialBalance;
  
  void deposit(double amount) {
    _balance += amount;
    print('Deposited \$$amount. New balance: \$$_balance');
  }
  
  void withdraw(double amount) {
    if (_balance >= amount) {
      _balance -= amount;
      print('Withdrew \$$amount. New balance: \$$_balance');
    } else {
      print('Insufficient funds');
    }
  }
  
  double getBalance() => _balance;
}

class DepositCommand extends Command {
  final BankAccount _account;
  final double _amount;
  
  DepositCommand(this._account, this._amount);
  
  @override
  void execute() {
    _account.deposit(_amount);
  }
  
  @override
  void undo() {
    _account.withdraw(_amount);
  }
}

class WithdrawCommand extends Command {
  final BankAccount _account;
  final double _amount;
  bool _success = false;
  
  WithdrawCommand(this._account, this._amount);
  
  @override
  void execute() {
    final oldBalance = _account.getBalance();
    _account.withdraw(_amount);
    _success = _account.getBalance() < oldBalance;
  }
  
  @override
  void undo() {
    if (_success) {
      _account.deposit(_amount);
    }
  }
}

// Demo code
void main() {
  print('=== Command Pattern Demo ===\n');
  
  // Example 1: Remote Control
  print('--- Remote Control Example ---');
  
  final livingRoomLight = Light();
  final livingRoomStereo = Stereo();
  
  final lightOn = LightOnCommand(livingRoomLight);
  final lightOff = LightOffCommand(livingRoomLight);
  final stereoOn = StereoOnCommand(livingRoomStereo);
  final stereoOff = StereoOffCommand(livingRoomStereo);
  
  final remote = RemoteControl();
  remote.setCommand(lightOn);
  remote.setCommand(lightOff);
  remote.setCommand(stereoOn);
  remote.setCommand(stereoOff);
  
  print('\nTurning on light (slot 0):');
  remote.buttonPressed(0);
  
  print('\nTurning on stereo (slot 2):');
  remote.buttonPressed(2);
  
  print('\nUndo last action:');
  remote.undoButtonPressed();
  
  print('\nTurning off light (slot 1):');
  remote.buttonPressed(1);
  
  print('\nUndo last action:');
  remote.undoButtonPressed();
  
  print('');
  
  // Example 2: Macro Command
  print('--- Macro Command Example ---');
  
  final partyMode = MacroCommand();
  partyMode.addCommand(lightOn);
  partyMode.addCommand(stereoOn);
  
  final shutdownMode = MacroCommand();
  shutdownMode.addCommand(stereoOff);
  shutdownMode.addCommand(lightOff);
  
  print('\nActivating party mode:');
  partyMode.execute();
  
  print('\nActivating shutdown mode:');
  shutdownMode.execute();
  
  print('\nUndo shutdown:');
  shutdownMode.undo();
  
  print('');
  
  // Example 3: Transaction Command
  print('--- Transaction Command Example ---');
  
  final myAccount = BankAccount(1000);
  
  print('\nInitial balance: \$${myAccount.getBalance()}');
  
  final deposit = DepositCommand(myAccount, 500);
  final withdraw = WithdrawCommand(myAccount, 200);
  
  print('\nExecuting deposit:');
  deposit.execute();
  
  print('\nExecuting withdrawal:');
  withdraw.execute();
  
  print('\nUndo withdrawal:');
  withdraw.undo();
  
  print('\nFinal balance: \$${myAccount.getBalance()}');
}
