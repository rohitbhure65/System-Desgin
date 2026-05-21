import 'interfaces.dart';
import 'vending_machine.dart';
import 'audio_player.dart';

void main() {
  print('=== State Pattern Demo ===\n');
  
  // Example 1: Vending Machine
  print('--- Vending Machine Example ---');
  
  final machine = VendingMachine(5);
  
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
  
  final player = AudioPlayer(10);
  
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
