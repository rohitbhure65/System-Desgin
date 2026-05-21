import { DrawingAPI, Device } from './interfaces';

export class RedCircleAPI implements DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void {
    console.log(`Drawing Circle [color: red, center: (${x}, ${y}), radius: ${radius}]`);
  }
  drawRectangle(x: number, y: number, width: number, height: number): void {
    console.log(`Drawing Rectangle [color: red, top-left: (${x}, ${y}), width: ${width}, height: ${height}]`);
  }
}

export class GreenCircleAPI implements DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void {
    console.log(`Drawing Circle [color: green, center: (${x}, ${y}), radius: ${radius}]`);
  }
  drawRectangle(x: number, y: number, width: number, height: number): void {
    console.log(`Drawing Rectangle [color: green, top-left: (${x}, ${y}), width: ${width}, height: ${height}]`);
  }
}

export class Television implements Device {
  private on: boolean = false;
  private volume: number = 10;
  
  turnOn(): void { this.on = true; console.log('TV is now ON'); }
  turnOff(): void { this.on = false; console.log('TV is now OFF'); }
  setVolume(volume: number): void {
    if (this.on) { this.volume = volume; console.log(`TV volume set to ${volume}`); }
    else { console.log('Cannot set volume: TV is OFF'); }
  }
  getVolume(): number { return this.volume; }
}

export class Radio implements Device {
  private on: boolean = false;
  private volume: number = 5;
  
  turnOn(): void { this.on = true; console.log('Radio is now ON'); }
  turnOff(): void { this.on = false; console.log('Radio is now OFF'); }
  setVolume(volume: number): void {
    if (this.on) { this.volume = volume; console.log(`Radio volume set to ${volume}`); }
    else { console.log('Cannot set volume: Radio is OFF'); }
  }
  getVolume(): number { return this.volume; }
}
