import { VendingMachine } from './vending_machine';
import { AudioPlayer } from './audio_player';

console.log('=== State Pattern Demo ===\n');

// Example 1: Vending Machine
console.log('--- Vending Machine Example ---');

const machine = new VendingMachine(5);

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

const player = new AudioPlayer(10);

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
