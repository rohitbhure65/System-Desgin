import { Mediator } from './interfaces';

export class SmartDevice {
  protected homeHub: Mediator;
  protected deviceName: string;
  protected isOn: boolean = false;
  
  constructor(hub: Mediator, name: string) {
    this.homeHub = hub;
    this.deviceName = name;
  }
  
  turnOn(): void {
    this.isOn = true;
    console.log(`${this.deviceName} turned ON`);
    this.homeHub.sendMessage(`${this.deviceName} turned ON`, this.deviceName);
  }
  
  turnOff(): void {
    this.isOn = false;
    console.log(`${this.deviceName} turned OFF`);
    this.homeHub.sendMessage(`${this.deviceName} turned OFF`, this.deviceName);
  }
  
  getName(): string {
    return this.deviceName;
  }
  
  getStatus(): boolean {
    return this.isOn;
  }
}

export class SmartLight extends SmartDevice {
  constructor(hub: Mediator, name: string) {
    super(hub, name);
  }
}

export class SmartThermostat extends SmartDevice {
  private temperature: number = 70;
  
  constructor(hub: Mediator, name: string) {
    super(hub, name);
  }
  
  setTemperature(temp: number): void {
    this.temperature = temp;
    console.log(`${this.getName()} set to ${this.temperature}°F`);
  }
  
  getTemperature(): number {
    return this.temperature;
  }
}

export class HomeHub implements Mediator {
  private devices: Map<string, SmartDevice> = new Map();
  
  addDevice(device: SmartDevice): void {
    this.devices.set(device.getName(), device);
  }
  
  sendMessage(message: string, sender: string): void {
    console.log(`Home Hub: ${message}`);
    
    if (sender.includes('Thermostat') && message.includes('turned ON')) {
      for (const [name, device] of this.devices) {
        if (name.includes('Light') && !device.getStatus()) {
          device.turnOn();
        }
      }
    }
  }
  
  activateAwayMode(): void {
    console.log('Home Hub: Activating away mode...');
    for (const [name, device] of this.devices) {
      if (device.getStatus()) {
        device.turnOff();
      }
    }
  }
  
  activateHomeMode(): void {
    console.log('Home Hub: Activating home mode...');
    for (const [name, device] of this.devices) {
      if (name.includes('Light')) {
        device.turnOn();
      }
    }
  }
}
