import 'receivers.dart';
import 'concrete_commands.dart';
import 'invoker.dart';
import 'macro_command.dart';

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
