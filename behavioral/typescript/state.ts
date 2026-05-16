/*
 * STATE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The State pattern allows an object to alter its behavior when its internal state changes.
 * The object appears to change its class by delegating state-specific behavior to different state objects.
 * 
 * WHY DOES IT EXIST?
 * - When an object's behavior depends on its state and must change at runtime
 * - When you have large conditional statements that switch between states
 * - When you want to avoid monolithic conditional logic
 * 
 * WHEN TO USE IT?
 * - When an object has many states and its behavior changes based on those states
 * - When you have large conditional operators that switch between states
 * - When you want to eliminate conditional logic from the main class
 * - Common use cases: game characters, vending machines, audio/video players, document editors
 * 
 * PROS:
 * - Single Responsibility Principle (each state is a separate class)
 * - Open/Closed Principle (can add new states without changing existing code)
 * - Eliminates conditional logic from the context
 * - Makes state transitions explicit
 * 
 * CONS:
 * - Can increase the number of classes in the system
 * - State transitions can be complex to manage
 * - May make the code more complex for simple scenarios
 * - Can lead to tight coupling between states
 * 
 * REAL-WORLD ANALOGY:
 * Think of a vending machine. It has different states: "No Coin", "Has Coin", "Dispensing", "Out of Stock". When you insert a coin, it transitions from "No Coin" to "Has Coin". When you press a button, it transitions to "Dispensing". The machine's behavior changes based on its current state, but the machine itself doesn't change - it just delegates to the appropriate state object.
 */

// State interface - declares the state-specific methods
interface State {
  insertCoin(): void;
  ejectCoin(): void;
  pressButton(): void;
  dispense(): void;
}

// Context - maintains a reference to the current state
class VendingMachine {
  private currentState: State;
  private coinCount: number = 0;
  private stockCount: number;
  
  constructor(initialStock: number) {
    this.stockCount = initialStock;
    // Initial state depends on stock
    if (initialStock > 0) {
      this.currentState = new NoCoinState(this);
    } else {
      this.currentState = new SoldOutState(this);
    }
  }
  
  setState(state: State): void {
    this.currentState = state;
  }
  
  insertCoin(): void {
    this.currentState.insertCoin();
  }
  
  ejectCoin(): void {
    this.currentState.ejectCoin();
  }
  
  pressButton(): void {
    this.currentState.pressButton();
  }
  
  dispense(): void {
    this.currentState.dispense();
  }
  
  addCoin(): void {
    this.coinCount++;
    console.log(`Coin inserted. Total coins: ${this.coinCount}`);
  }
  
  returnCoin(): void {
    if (this.coinCount > 0) {
      this.coinCount--;
      console.log(`Coin returned. Total coins: ${this.coinCount}`);
    }
  }
  
  releaseProduct(): void {
    if (this.stockCount > 0) {
      this.stockCount--;
      this.coinCount--;
      console.log(`Product dispensed. Stock: ${this.stockCount}, Coins: ${this.coinCount}`);
    }
  }
  
  getCoinCount(): number {
    return this.coinCount;
  }
  
  getStockCount(): number {
    return this.stockCount;
  }
}

// Concrete State 1: No Coin
class NoCoinState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Coin inserted...');
    this.machine.addCoin();
    this.machine.setState(new HasCoinState(this.machine));
  }
  
  ejectCoin(): void {
    console.log('No coin to eject');
  }
  
  pressButton(): void {
    console.log('Please insert a coin first');
  }
  
  dispense(): void {
    console.log('Please insert a coin first');
  }
}

// Concrete State 2: Has Coin
class HasCoinState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Coin already inserted');
  }
  
  ejectCoin(): void {
    console.log('Coin ejected');
    this.machine.returnCoin();
    this.machine.setState(new NoCoinState(this.machine));
  }
  
  pressButton(): void {
    console.log('Button pressed...');
    if (this.machine.getStockCount() > 0) {
      this.machine.setState(new DispensingState(this.machine));
      this.machine.dispense();
    } else {
      console.log('Out of stock');
      this.machine.setState(new SoldOutState(this.machine));
    }
  }
  
  dispense(): void {
    console.log('Press button to dispense');
  }
}

// Concrete State 3: Dispensing
class DispensingState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Please wait, dispensing...');
  }
  
  ejectCoin(): void {
    console.log('Cannot eject during dispensing');
  }
  
  pressButton(): void {
    console.log('Already dispensing...');
  }
  
  dispense(): void {
    this.machine.releaseProduct();
    if (this.machine.getStockCount() > 0) {
      this.machine.setState(new NoCoinState(this.machine));
    } else {
      this.machine.setState(new SoldOutState(this.machine));
    }
  }
}

// Concrete State 4: Sold Out
class SoldOutState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Cannot insert coin, machine is sold out');
  }
  
  ejectCoin(): void {
    console.log('Cannot eject, no coin inserted');
  }
  
  pressButton(): void {
    console.log('Machine is sold out');
  }
  
  dispense(): void {
    console.log('Machine is sold out');
  }
}

// Example 2: Audio Player States
// Shows how State can be used for media players

interface AudioPlayerState {
  clickPlay(): void;
  clickStop(): void;
  clickNext(): void;
  clickPrevious(): void;
}

class AudioPlayer {
  private currentState: AudioPlayerState;
  private isPlaying: boolean = false;
  private currentTrack: number = 1;
  private totalTracks: number;
  
  constructor(tracks: number) {
    this.totalTracks = tracks;
    this.currentState = new StoppedState(this);
  }
  
  setState(state: AudioPlayerState): void {
    this.currentState = state;
  }
  
  clickPlay(): void {
    this.currentState.clickPlay();
  }
  
  clickStop(): void {
    this.currentState.clickStop();
  }
  
  clickNext(): void {
    this.currentState.clickNext();
  }
  
  clickPrevious(): void {
    this.currentState.clickPrevious();
  }
  
  startPlaying(): void {
    this.isPlaying = true;
    console.log(`Started playing track ${this.currentTrack}`);
  }
  
  stopPlaying(): void {
    this.isPlaying = false;
    console.log('Stopped playing');
  }
  
  nextTrack(): void {
    this.currentTrack = (this.currentTrack % this.totalTracks) + 1;
    console.log(`Moved to track ${this.currentTrack}`);
  }
  
  previousTrack(): void {
    this.currentTrack = this.currentTrack === 1 ? this.totalTracks : this.currentTrack - 1;
    console.log(`Moved to track ${this.currentTrack}`);
  }
  
  getIsPlaying(): boolean {
    return this.isPlaying;
  }
}

class PlayingState implements AudioPlayerState {
  private player: AudioPlayer;
  
  constructor(player: AudioPlayer) {
    this.player = player;
  }
  
  clickPlay(): void {
    console.log('Already playing');
  }
  
  clickStop(): void {
    console.log('Stopping playback...');
    this.player.stopPlaying();
    this.player.setState(new StoppedState(this.player));
  }
  
  clickNext(): void {
    console.log('Skipping to next track...');
    this.player.nextTrack();
  }
  
  clickPrevious(): void {
    console.log('Going to previous track...');
    this.player.previousTrack();
  }
}

class StoppedState implements AudioPlayerState {
  private player: AudioPlayer;
  
  constructor(player: AudioPlayer) {
    this.player = player;
  }
  
  clickPlay(): void {
    console.log('Starting playback...');
    this.player.startPlaying();
    this.player.setState(new PlayingState(this.player));
  }
  
  clickStop(): void {
    console.log('Already stopped');
  }
  
  clickNext(): void {
    console.log('Skipping to next track...');
    this.player.nextTrack();
  }
  
  clickPrevious(): void {
    console.log('Going to previous track...');
    this.player.previousTrack();
  }
}

// Demo code
console.log('=== State Pattern Demo ===\n');

// Example 1: Vending Machine
console.log('--- Vending Machine Example ---');

const machine = new VendingMachine(5);  // 5 items in stock

console.log('\nAttempt to press button without coin:');
machine.pressButton();

console.log('\nInsert coin:');
machine.insertCoin();

console.log('\nPress button:');
machine.pressButton();

console.log('\nInsert another coin:');
machine.insertCoin();

console.log('\nPress button:');
machine.pressButton();

console.log('\nEject coin:');
machine.ejectCoin();

console.log('');

// Example 2: Audio Player
console.log('--- Audio Player Example ---');

const player = new AudioPlayer(10);  // 10 tracks

console.log('\nClick play (stopped state):');
player.clickPlay();

console.log('\nClick next:');
player.clickNext();

console.log('\nClick stop:');
player.clickStop();

console.log('\nClick previous:');
player.clickPrevious();

console.log('\nClick play again:');
player.clickPlay();
