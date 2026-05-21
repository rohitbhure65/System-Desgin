export interface DrawingAPI {
  drawCircle(x: number, y: number, radius: number): void;
  drawRectangle(x: number, y: number, width: number, height: number): void;
}

export interface Device {
  turnOn(): void;
  turnOff(): void;
  setVolume(volume: number): void;
  getVolume(): number;
}
