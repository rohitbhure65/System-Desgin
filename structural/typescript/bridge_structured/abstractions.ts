import { DrawingAPI, Device } from './interfaces';

export abstract class Shape {
  protected drawingAPI: DrawingAPI;
  constructor(api: DrawingAPI) { this.drawingAPI = api; }
  abstract draw(): void;
  abstract resize(percentage: number): void;
}

export class Circle extends Shape {
  private x: number;
  private y: number;
  private radius: number;
  
  constructor(x: number, y: number, radius: number, api: DrawingAPI) {
    super(api);
    this.x = x; this.y = y; this.radius = radius;
  }
  draw(): void { this.drawingAPI.drawCircle(this.x, this.y, this.radius); }
  resize(percentage: number): void {
    this.radius *= percentage / 100;
    console.log(`Resizing circle to ${this.radius} radius`);
  }
}

export class Rectangle extends Shape {
  private x: number;
  private y: number;
  private width: number;
  private height: number;
  
  constructor(x: number, y: number, width: number, height: number, api: DrawingAPI) {
    super(api);
    this.x = x; this.y = y; this.width = width; this.height = height;
  }
  draw(): void { this.drawingAPI.drawRectangle(this.x, this.y, this.width, this.height); }
  resize(percentage: number): void {
    this.width *= percentage / 100;
    this.height *= percentage / 100;
    console.log(`Resizing rectangle to ${this.width}x${this.height}`);
  }
}

export class RemoteControl {
  protected device: Device;
  constructor(device: Device) { this.device = device; }
  
  togglePower(): void {
    if (this.device.getVolume() >= 0) { this.device.turnOff(); }
    else { this.device.turnOn(); }
  }
  volumeUp(): void { this.device.setVolume(this.device.getVolume() + 1); }
  volumeDown(): void { this.device.setVolume(this.device.getVolume() - 1); }
}

export class AdvancedRemoteControl extends RemoteControl {
  mute(): void {
    console.log('Muting device');
    this.device.setVolume(0);
  }
}
