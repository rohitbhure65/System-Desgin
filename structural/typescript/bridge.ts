/*
 * BRIDGE DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Bridge pattern separates abstraction from implementation so that both can vary independently.
 * It uses composition instead of inheritance to decouple the abstraction from its implementation.
 * 
 * WHY DOES IT EXIST?
 * - When you want to avoid a permanent binding between an abstraction and its implementation
 * - When both the abstraction and the implementation should be extensible by subclassing
 * - When changes in the implementation should not affect clients
 * - When you have a class hierarchy that explodes due to combining multiple dimensions
 * 
 * WHEN TO USE IT?
 * - When you want to split a monolithic class that has several variants of some functionality
 * - When you need to extend a class in several independent dimensions
 * - When you want to be able to switch implementations at runtime
 * - Common use cases: UI frameworks (different controls on different platforms), shape rendering, device drivers
 * 
 * PROS:
 * - Separates abstraction from implementation
 * - Improves extensibility (can extend abstractions and implementations independently)
 * - Hides implementation details from clients
 * - Reduces the number of subclasses needed (avoids combinatorial explosion)
 * 
 * CONS:
 * - Increases code complexity
 * - May require additional indirection
 * - Can make the code harder to understand initially
 * - Might be overkill for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a TV remote control (abstraction) and the TV itself (implementation). The remote control doesn't need to know the internal workings of the TV. You can use the same remote with different TV brands, and different remotes with the same TV. The remote (abstraction) is bridged to the TV (implementation) through a standard interface (infrared signals).
 */

// Implementation Interface - defines the operations for all concrete implementations
interface DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void;
  drawRectangle(x: number, y: number, width: number, height: number): void;
}

// Concrete Implementation 1: Red Circle API
class RedCircleAPI implements DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void {
    console.log(`Drawing Circle [color: red, center: (${x}, ${y}), radius: ${radius}]`);
  }
  
  drawRectangle(x: number, y: number, width: number, height: number): void {
    console.log(`Drawing Rectangle [color: red, top-left: (${x}, ${y}), width: ${width}, height: ${height}]`);
  }
}

// Concrete Implementation 2: Green Circle API
class GreenCircleAPI implements DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void {
    console.log(`Drawing Circle [color: green, center: (${x}, ${y}), radius: ${radius}]`);
  }
  
  drawRectangle(x: number, y: number, width: number, height: number): void {
    console.log(`Drawing Rectangle [color: green, top-left: (${x}, ${y}), width: ${width}, height: ${height}]`);
  }
}

// Abstraction - defines the abstraction's interface and maintains a reference to an implementation
abstract class Shape {
  protected drawingAPI: DrawingAPI;
  
  constructor(api: DrawingAPI) {
    this.drawingAPI = api;
  }
  
  abstract draw(): void;
  abstract resize(percentage: number): void;
}

// Refined Abstraction 1: Circle
class Circle extends Shape {
  private x: number;
  private y: number;
  private radius: number;
  
  constructor(x: number, y: number, radius: number, api: DrawingAPI) {
    super(api);
    this.x = x;
    this.y = y;
    this.radius = radius;
  }
  
  draw(): void {
    this.drawingAPI.drawCircle(this.x, this.y, this.radius);
  }
  
  resize(percentage: number): void {
    this.radius *= percentage / 100;
    console.log(`Resizing circle to ${this.radius} radius`);
  }
}

// Refined Abstraction 2: Rectangle
class Rectangle extends Shape {
  private x: number;
  private y: number;
  private width: number;
  private height: number;
  
  constructor(x: number, y: number, width: number, height: number, api: DrawingAPI) {
    super(api);
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
  }
  
  draw(): void {
    this.drawingAPI.drawRectangle(this.x, this.y, this.width, this.height);
  }
  
  resize(percentage: number): void {
    this.width *= percentage / 100;
    this.height *= percentage / 100;
    console.log(`Resizing rectangle to ${this.width}x${this.height}`);
  }
}

// Example 2: Device and Remote Control Bridge
// This shows how the Bridge pattern can be used for device control

// Implementation Interface
interface Device {
  turnOn(): void;
  turnOff(): void;
  setVolume(volume: number): void;
  getVolume(): number;
}

// Concrete Implementation 1: TV
class Television implements Device {
  private on: boolean = false;
  private volume: number = 10;
  
  turnOn(): void {
    this.on = true;
    console.log('TV is now ON');
  }
  
  turnOff(): void {
    this.on = false;
    console.log('TV is now OFF');
  }
  
  setVolume(volume: number): void {
    if (this.on) {
      this.volume = volume;
      console.log(`TV volume set to ${volume}`);
    } else {
      console.log('Cannot set volume: TV is OFF');
    }
  }
  
  getVolume(): number {
    return this.volume;
  }
}

// Concrete Implementation 2: Radio
class Radio implements Device {
  private on: boolean = false;
  private volume: number = 5;
  
  turnOn(): void {
    this.on = true;
    console.log('Radio is now ON');
  }
  
  turnOff(): void {
    this.on = false;
    console.log('Radio is now OFF');
  }
  
  setVolume(volume: number): void {
    if (this.on) {
      this.volume = volume;
      console.log(`Radio volume set to ${volume}`);
    } else {
      console.log('Cannot set volume: Radio is OFF');
    }
  }
  
  getVolume(): number {
    return this.volume;
  }
}

// Abstraction: Remote Control
class RemoteControl {
  protected device: Device;
  
  constructor(device: Device) {
    this.device = device;
  }
  
  togglePower(): void {
    if (this.device.getVolume() >= 0) {
      this.device.turnOff();
    } else {
      this.device.turnOn();
    }
  }
  
  volumeUp(): void {
    const currentVolume = this.device.getVolume();
    this.device.setVolume(currentVolume + 1);
  }
  
  volumeDown(): void {
    const currentVolume = this.device.getVolume();
    this.device.setVolume(currentVolume - 1);
  }
}

// Refined Abstraction: Advanced Remote Control
class AdvancedRemoteControl extends RemoteControl {
  mute(): void {
    console.log('Muting device');
    this.device.setVolume(0);
  }
}

// Demo code
function demoBridge(): void {
  console.log('=== Bridge Pattern Demo ===\n');
  
  // Example 1: Shape Drawing Bridge
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
  
  // Example 2: Device and Remote Control Bridge
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

// Run the demo
demoBridge();
