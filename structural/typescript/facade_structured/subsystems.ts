export class CPU {
  freeze(): void { console.log('CPU: Freezing...'); }
  jump(position: number): void { console.log(`CPU: Jumping to position \${position}`); }
  execute(): void { console.log('CPU: Executing instructions...'); }
}

export class Memory {
  load(position: number, data: string): void { console.log(`Memory: Loading data '\${data}' at position \${position}`); }
}

export class HardDrive {
  read(lba: number, size: number): string {
    console.log(`HardDrive: Reading \${size} bytes from LBA \${lba}`);
    return 'Boot Data';
  }
}

export class Amplifier {
  on(): void { console.log('Amplifier: ON'); }
  off(): void { console.log('Amplifier: OFF'); }
  setVolume(level: number): void { console.log(`Amplifier: Volume set to \${level}`); }
}

export class Tuner {
  on(): void { console.log('Tuner: ON'); }
  off(): void { console.log('Tuner: OFF'); }
  setFrequency(freq: number): void { console.log(`Tuner: Frequency set to \${freq} FM`); }
}

export class DVDPlayer {
  on(): void { console.log('DVD Player: ON'); }
  off(): void { console.log('DVD Player: OFF'); }
  play(movie: string): void { console.log(`DVD Player: Playing '\${movie}'`); }
}

export class Projector {
  on(): void { console.log('Projector: ON'); }
  off(): void { console.log('Projector: OFF'); }
  setInput(input: string): void { console.log(`Projector: Input set to \${input}`); }
}

export class TheaterLights {
  on(): void { console.log('Theater Lights: ON'); }
  off(): void { console.log('Theater Lights: OFF'); }
  dim(level: number): void { console.log(`Theater Lights: Dimmed to \${level}%`); }
}

export class Screen {
  up(): void { console.log('Screen: UP'); }
  down(): void { console.log('Screen: DOWN'); }
}

export class PopcornPopper {
  on(): void { console.log('Popcorn Popper: ON'); }
  off(): void { console.log('Popcorn Popper: OFF'); }
  pop(): void { console.log('Popcorn Popper: Popping popcorn!'); }
}

export class InventorySystem {
  checkInventory(item: string, quantity: number): boolean {
    console.log(`Inventory: Checking \${quantity} units of \${item}`);
    return true;
  }
  updateInventory(item: string, quantity: number): void {
    console.log(`Inventory: Updating \${quantity} units of \${item}`);
  }
}

export class PaymentSystem {
  processPayment(amount: number): boolean {
    console.log(`Payment: Processing payment of $\${amount}`);
    return true;
  }
  refundPayment(amount: number): void {
    console.log(`Payment: Refunding $\${amount}`);
  }
}

export class ShippingSystem {
  scheduleShipping(address: string): void { console.log(`Shipping: Scheduling delivery to \${address}`); }
  cancelShipping(): void { console.log('Shipping: Cancelling delivery'); }
}

export class NotificationSystem {
  sendConfirmation(email: string): void { console.log(`Notification: Sending confirmation to \${email}`); }
  sendCancellation(email: string): void { console.log(`Notification: Sending cancellation to \${email}`); }
}
