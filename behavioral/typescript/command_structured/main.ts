import { Light, Stereo, BankAccount } from './receivers';
import { LightOnCommand, LightOffCommand, StereoOnCommand, StereoOffCommand, DepositCommand, WithdrawCommand } from './concrete_commands';
import { RemoteControl } from './invoker';
import { MacroCommand } from './macro_command';

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
