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
abstract class State {
  void insertCoin();
  void ejectCoin();
  void pressButton();
  void dispense();
}

// Context - maintains a reference to the current state
class VendingMachine {
  late State _currentState;
  int _coinCount = 0;
  int _stockCount;
  
  VendingMachine(this._stockCount) {
    // Initial state depends on stock
    if (_stockCount > 0) {
      _currentState = NoCoinState(this);
    } else {
      _currentState = SoldOutState(this);
    }
  }
  
  void setState(State state) {
    _currentState = state;
  }
  
  void insertCoin() {
    _currentState.insertCoin();
  }
  
  void ejectCoin() {
    _currentState.ejectCoin();
  }
  
  void pressButton() {
    _currentState.pressButton();
  }
  
  void dispense() {
    _currentState.dispense();
  }
  
  void addCoin() {
    _coinCount++;
    print('Coin inserted. Total coins: $_coinCount');
  }
  
  void returnCoin() {
    if (_coinCount > 0) {
      _coinCount--;
      print('Coin returned. Total coins: $_coinCount');
    }
  }
  
  void releaseProduct() {
    if (_stockCount > 0) {
      _stockCount--;
      _coinCount--;
      print('Product dispensed. Stock: $_stockCount, Coins: $_coinCount');
    }
  }
  
  int get coinCount => _coinCount;
  int get stockCount => _stockCount;
}

// Concrete State 1: No Coin
class NoCoinState implements State {
  final VendingMachine _machine;
  
  NoCoinState(this._machine);
  
  @override
  void insertCoin() {
    print('Coin inserted...');
    _machine.addCoin();
    _machine.setState(HasCoinState(_machine));
  }
  
  @override
  void ejectCoin() {
    print('No coin to eject');
  }
  
  @override
  void pressButton() {
    print('Please insert a coin first');
  }
  
  @override
  void dispense() {
    print('Please insert a coin first');
  }
}

// Concrete State 2: Has Coin
class HasCoinState implements State {
  final VendingMachine _machine;
  
  HasCoinState(this._machine);
  
  @override
  void insertCoin() {
    print('Coin already inserted');
  }
  
  @override
  void ejectCoin() {
    print('Coin ejected');
    _machine.returnCoin();
    _machine.setState(NoCoinState(_machine));
  }
  
  @override
  void pressButton() {
    print('Button pressed...');
    if (_machine.stockCount > 0) {
      _machine.setState(DispensingState(_machine));
      _machine.dispense();
    } else {
      print('Out of stock');
      _machine.setState(SoldOutState(_machine));
    }
  }
  
  @override
  void dispense() {
    print('Press button to dispense');
  }
}

// Concrete State 3: Dispensing
class DispensingState implements State {
  final VendingMachine _machine;
  
  DispensingState(this._machine);
  
  @override
  void insertCoin() {
    print('Please wait, dispensing...');
  }
  
  @override
  void ejectCoin() {
    print('Cannot eject during dispensing');
  }
  
  @override
  void pressButton() {
    print('Already dispensing...');
  }
  
  @override
  void dispense() {
    _machine.releaseProduct();
    if (_machine.stockCount > 0) {
      _machine.setState(NoCoinState(_machine));
    } else {
      _machine.setState(SoldOutState(_machine));
    }
  }
}

// Concrete State 4: Sold Out
class SoldOutState implements State {
  SoldOutState(VendingMachine machine);
  
  @override
  void insertCoin() {
    print('Cannot insert coin, machine is sold out');
  }
  
  @override
  void ejectCoin() {
    print('Cannot eject, no coin inserted');
  }
  
  @override
  void pressButton() {
    print('Machine is sold out');
  }
  
  @override
  void dispense() {
    print('Machine is sold out');
  }
}

// Example 2: Audio Player States
// Shows how State can be used for media players

abstract class AudioPlayerState {
  void clickPlay();
  void clickStop();
  void clickNext();
  void clickPrevious();
}

class AudioPlayer {
  late AudioPlayerState _currentState;
  bool _isPlaying = false;
  int _currentTrack = 1;
  int _totalTracks;
  
  AudioPlayer(this._totalTracks) {
    _currentState = StoppedState(this);
  }
  
  void setState(AudioPlayerState state) {
    _currentState = state;
  }
  
  void clickPlay() {
    _currentState.clickPlay();
  }
  
  void clickStop() {
    _currentState.clickStop();
  }
  
  void clickNext() {
    _currentState.clickNext();
  }
  
  void clickPrevious() {
    _currentState.clickPrevious();
  }
  
  void startPlaying() {
    _isPlaying = true;
    print('Started playing track $_currentTrack');
  }
  
  void stopPlaying() {
    _isPlaying = false;
    print('Stopped playing');
  }
  
  void nextTrack() {
    _currentTrack = (_currentTrack % _totalTracks) + 1;
    print('Moved to track $_currentTrack');
  }
  
  void previousTrack() {
    _currentTrack = _currentTrack == 1 ? _totalTracks : _currentTrack - 1;
    print('Moved to track $_currentTrack');
  }
  
  bool get isPlaying => _isPlaying;
}

class PlayingState implements AudioPlayerState {
  final AudioPlayer _player;
  
  PlayingState(this._player);
  
  @override
  void clickPlay() {
    print('Already playing');
  }
  
  @override
  void clickStop() {
    print('Stopping playback...');
    _player.stopPlaying();
    _player.setState(StoppedState(_player));
  }
  
  @override
  void clickNext() {
    print('Skipping to next track...');
    _player.nextTrack();
  }
  
  @override
  void clickPrevious() {
    print('Going to previous track...');
    _player.previousTrack();
  }
}

class StoppedState implements AudioPlayerState {
  final AudioPlayer _player;
  
  StoppedState(this._player);
  
  @override
  void clickPlay() {
    print('Starting playback...');
    _player.startPlaying();
    _player.setState(PlayingState(_player));
  }
  
  @override
  void clickStop() {
    print('Already stopped');
  }
  
  @override
  void clickNext() {
    print('Skipping to next track...');
    _player.nextTrack();
  }
  
  @override
  void clickPrevious() {
    print('Going to previous track...');
    _player.previousTrack();
  }
}

// Demo code
void main() {
  print('=== State Pattern Demo ===\n');
  
  // Example 1: Vending Machine
  print('--- Vending Machine Example ---');
  
  final machine = VendingMachine(5);  // 5 items in stock
  
  print('\nAttempt to press button without coin:');
  machine.pressButton();
  
  print('\nInsert coin:');
  machine.insertCoin();
  
  print('\nPress button:');
  machine.pressButton();
  
  print('\nInsert another coin:');
  machine.insertCoin();
  
  print('\nPress button:');
  machine.pressButton();
  
  print('\nEject coin:');
  machine.ejectCoin();
  
  print('');
  
  // Example 2: Audio Player
  print('--- Audio Player Example ---');
  
  final player = AudioPlayer(10);  // 10 tracks
  
  print('\nClick play (stopped state):');
  player.clickPlay();
  
  print('\nClick next:');
  player.clickNext();
  
  print('\nClick stop:');
  player.clickStop();
  
  print('\nClick previous:');
  player.clickPrevious();
  
  print('\nClick play again:');
  player.clickPlay();
}
