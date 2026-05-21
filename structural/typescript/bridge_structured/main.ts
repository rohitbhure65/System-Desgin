import { RedCircleAPI, GreenCircleAPI, Television, Radio } from './implementations';
import { Circle, Rectangle, RemoteControl, AdvancedRemoteControl } from './abstractions';

function demoBridge(): void {
  console.log('=== Bridge Pattern Demo ===\n');
  
  console.log('--- Shape Drawing Bridge ---');
  const redCircle = new Circle(100, 100, 10, new RedCircleAPI());
  const greenCircle = new Circle(100, 100, 10, new GreenCircleAPI());
  redCircle.draw();
  greenCircle.draw();
  
  const redRectangle = new Rectangle(50, 50, 20, 30, new RedCircleAPI());
  const greenRectangle = new Rectangle(50, 50, 20, 30, new GreenCircleAPI());
  redRectangle.draw();
  greenRectangle.draw();
  
  console.log('\nResizing shapes:');
  redCircle.resize(150);
  redCircle.draw();
  console.log();
  
  console.log('--- Device and Remote Control Bridge ---');
  const tv = new Television();
  const tvRemote = new RemoteControl(tv);
  
  console.log('\nControlling TV with basic remote:');
  tvRemote.togglePower();
  tvRemote.volumeUp();
  tvRemote.volumeUp();
  tvRemote.volumeDown();
  tvRemote.togglePower();
  
  const radio = new Radio();
  const advancedRemote = new AdvancedRemoteControl(radio);
  
  console.log('\nControlling Radio with advanced remote:');
  advancedRemote.togglePower();
  advancedRemote.volumeUp();
  advancedRemote.mute();
  advancedRemote.togglePower();
}

demoBridge();
