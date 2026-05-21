export class House {
  private foundation: string = '';
  private structure: string = '';
  private roof: string = '';
  private interior: string = '';
  private hasGarage: boolean = false;
  private hasGarden: boolean = false;
  private hasSwimmingPool: boolean = false;
  
  setFoundation(f: string): void { this.foundation = f; }
  setStructure(s: string): void { this.structure = s; }
  setRoof(r: string): void { this.roof = r; }
  setInterior(i: string): void { this.interior = i; }
  setGarage(g: boolean): void { this.hasGarage = g; }
  setGarden(g: boolean): void { this.hasGarden = g; }
  setSwimmingPool(s: boolean): void { this.hasSwimmingPool = s; }
  
  display(): void {
    console.log('=== House Details ===');
    console.log(`Foundation: ${this.foundation}`);
    console.log(`Structure: ${this.structure}`);
    console.log(`Roof: ${this.roof}`);
    console.log(`Interior: ${this.interior}`);
    console.log(`Garage: ${this.hasGarage ? 'Yes' : 'No'}`);
    console.log(`Garden: ${this.hasGarden ? 'Yes' : 'No'}`);
    console.log(`Swimming Pool: ${this.hasSwimmingPool ? 'Yes' : 'No'}`);
    console.log('====================');
  }
}

export class Computer {
  private cpu: string = '';
  private gpu: string = '';
  private ram: number = 8;
  private storage: number = 256;
  private hasWifi: boolean = false;
  private hasBluetooth: boolean = false;
  
  setCpu(cpu: string): void { this.cpu = cpu; }
  setGpu(gpu: string): void { this.gpu = gpu; }
  setRam(ram: number): void { this.ram = ram; }
  setStorage(storage: number): void { this.storage = storage; }
  setWifi(wifi: boolean): void { this.hasWifi = wifi; }
  setBluetooth(bluetooth: boolean): void { this.hasBluetooth = bluetooth; }
  
  display(): void {
    console.log('=== Computer Specs ===');
    console.log(`CPU: ${this.cpu}`);
    console.log(`GPU: ${this.gpu}`);
    console.log(`RAM: ${this.ram} GB`);
    console.log(`Storage: ${this.storage} GB`);
    console.log(`WiFi: ${this.hasWifi ? 'Yes' : 'No'}`);
    console.log(`Bluetooth: ${this.hasBluetooth ? 'Yes' : 'No'}`);
    console.log('=====================');
  }
}
