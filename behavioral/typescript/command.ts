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
  on(): void {
    console.log('Light is ON');
  }
  
  off(): void {
    console.log('Light is OFF');
  }
}

class Stereo {
  on(): void {
    console.log('Stereo is ON');
  }
  
  off(): void {
    console.log('Stereo is OFF');
  }
  
  setVolume(level: number): void {
    console.log(`Stereo volume set to ${level}`);
  }
}

// Command interface - declares the execute method
interface Command {
  execute(): void;
  undo(): void;
}

// Concrete Command 1: Light On
class LightOnCommand implements Command {
  private light: Light;
  
  constructor(light: Light) {
    this.light = light;
  }
  
  execute(): void {
    this.light.on();
  }
  
  undo(): void {
    this.light.off();
  }
}

// Concrete Command 2: Light Off
class LightOffCommand implements Command {
  private light: Light;
  
  constructor(light: Light) {
    this.light = light;
  }
  
  execute(): void {
    this.light.off();
  }
  
  undo(): void {
    this.light.on();
  }
}

// Concrete Command 3: Stereo On with Volume
class StereoOnCommand implements Command {
  private stereo: Stereo;
  private previousVolume: number = 0;
  
  constructor(stereo: Stereo) {
    this.stereo = stereo;
  }
  
  execute(): void {
    this.stereo.on();
    this.stereo.setVolume(10);
    this.previousVolume = 10;
  }
  
  undo(): void {
    this.stereo.setVolume(this.previousVolume);
    this.stereo.off();
  }
}

// Concrete Command 4: Stereo Off
class StereoOffCommand implements Command {
  private stereo: Stereo;
  
  constructor(stereo: Stereo) {
    this.stereo = stereo;
  }
  
  execute(): void {
    this.stereo.off();
  }
  
  undo(): void {
    this.stereo.on();
  }
}

// Invoker - asks the command to carry out the request
class RemoteControl {
  private commandHistory: Command[] = [];
  private undoStack: Command[] = [];
  
  setCommand(command: Command): void {
    this.commandHistory.push(command);
  }
  
  buttonPressed(slot: number): void {
    if (slot < this.commandHistory.length) {
      this.commandHistory[slot].execute();
      this.undoStack.push(this.commandHistory[slot]);
    }
  }
  
  undoButtonPressed(): void {
    if (this.undoStack.length > 0) {
      const command = this.undoStack.pop()!;
      command.undo();
    } else {
      console.log('Nothing to undo');
    }
  }
}

// Example 2: Macro Command
// Shows how multiple commands can be combined into one

class MacroCommand implements Command {
  private commands: Command[] = [];
  
  addCommand(command: Command): void {
    this.commands.push(command);
  }
  
  execute(): void {
    for (const command of this.commands) {
      command.execute();
    }
  }
  
  undo(): void {
    // Undo in reverse order
    for (let i = this.commands.length - 1; i >= 0; i--) {
      this.commands[i].undo();
    }
  }
}

// Example 3: Transaction Command
// Shows how Command can be used for transactional operations

class BankAccount {
  private balance: number;
  
  constructor(initialBalance: number = 0) {
    this.balance = initialBalance;
  }
  
  deposit(amount: number): void {
    this.balance += amount;
    console.log(`Deposited $${amount}. New balance: $${this.balance}`);
  }
  
  withdraw(amount: number): void {
    if (this.balance >= amount) {
      this.balance -= amount;
      console.log(`Withdrew $${amount}. New balance: $${this.balance}`);
    } else {
      console.log('Insufficient funds');
    }
  }
  
  getBalance(): number {
    return this.balance;
  }
}

class DepositCommand implements Command {
  private account: BankAccount;
  private amount: number;
  
  constructor(account: BankAccount, amount: number) {
    this.account = account;
    this.amount = amount;
  }
  
  execute(): void {
    this.account.deposit(this.amount);
  }
  
  undo(): void {
    this.account.withdraw(this.amount);
  }
}

class WithdrawCommand implements Command {
  private account: BankAccount;
  private amount: number;
  private success: boolean = false;
  
  constructor(account: BankAccount, amount: number) {
    this.account = account;
    this.amount = amount;
  }
  
  execute(): void {
    const oldBalance = this.account.getBalance();
    this.account.withdraw(this.amount);
    this.success = this.account.getBalance() < oldBalance;
  }
  
  undo(): void {
    if (this.success) {
      this.account.deposit(this.amount);
    }
  }
}

// Demo code
console.log('=== Command Pattern Demo ===\n');

// Example 1: Remote Control
console.log('--- Remote Control Example ---');

const livingRoomLight = new Light();
const livingRoomStereo = new Stereo();

const lightOn = new LightOnCommand(livingRoomLight);
const lightOff = new LightOffCommand(livingRoomLight);
const stereoOn = new StereoOnCommand(livingRoomStereo);
const stereoOff = new StereoOffCommand(livingRoomStereo);

const remote = new RemoteControl();
remote.setCommand(lightOn);
remote.setCommand(lightOff);
remote.setCommand(stereoOn);
remote.setCommand(stereoOff);

console.log('\nTurning on light (slot 0):');
remote.buttonPressed(0);

console.log('\nTurning on stereo (slot 2):');
remote.buttonPressed(2);

console.log('\nUndo last action:');
remote.undoButtonPressed();

console.log('\nTurning off light (slot 1):');
remote.buttonPressed(1);

console.log('\nUndo last action:');
remote.undoButtonPressed();

console.log('');

// Example 2: Macro Command
console.log('--- Macro Command Example ---');

const partyMode = new MacroCommand();
partyMode.addCommand(lightOn);
partyMode.addCommand(stereoOn);

const shutdownMode = new MacroCommand();
shutdownMode.addCommand(stereoOff);
shutdownMode.addCommand(lightOff);

console.log('\nActivating party mode:');
partyMode.execute();

console.log('\nActivating shutdown mode:');
shutdownMode.execute();

console.log('\nUndo shutdown:');
shutdownMode.undo();

console.log('');

// Example 3: Transaction Command
console.log('--- Transaction Command Example ---');

const myAccount = new BankAccount(1000);

console.log('\nInitial balance: $' + myAccount.getBalance());

const deposit = new DepositCommand(myAccount, 500);
const withdraw = new WithdrawCommand(myAccount, 200);

console.log('\nExecuting deposit:');
deposit.execute();

console.log('\nExecuting withdrawal:');
withdraw.execute();

console.log('\nUndo withdrawal:');
withdraw.undo();

console.log('\nFinal balance: $' + myAccount.getBalance());
