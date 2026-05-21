import 'implementations.dart';
import 'abstractions.dart';

void main() {
  print('=== Bridge Pattern Demo ===\n');
  
  print('--- Shape Drawing Bridge ---');
  
  var redCircle = Circle(100, 100, 10, RedCircleAPI());
  var greenCircle = Circle(100, 100, 10, GreenCircleAPI());
  
  redCircle.draw();
  greenCircle.draw();
  
  var redRectangle = Rectangle(50, 50, 20, 30, RedCircleAPI());
  var greenRectangle = Rectangle(50, 50, 20, 30, GreenCircleAPI());
  
  redRectangle.draw();
  greenRectangle.draw();
  
  print('\nResizing shapes:');
  redCircle.resize(150);
  redCircle.draw();
  
  print('');
  
  print('--- Device and Remote Control Bridge ---');
  
  var tv = Television();
  var tvRemote = RemoteControl(tv);
  
  print('\nControlling TV with basic remote:');
  tvRemote.togglePower();
  tvRemote.volumeUp();
  tvRemote.volumeUp();
  tvRemote.volumeDown();
  tvRemote.togglePower();
  
  var radio = Radio();
  var advancedRemote = AdvancedRemoteControl(radio);
  
  print('\nControlling Radio with advanced remote:');
  advancedRemote.togglePower();
  advancedRemote.volumeUp();
  advancedRemote.mute();
  advancedRemote.togglePower();
}
