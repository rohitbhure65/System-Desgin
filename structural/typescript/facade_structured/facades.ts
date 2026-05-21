import { CPU, Memory, HardDrive, Amplifier, Tuner, DVDPlayer, Projector, TheaterLights, Screen, PopcornPopper, InventorySystem, PaymentSystem, ShippingSystem, NotificationSystem } from './subsystems';

export class ComputerFacade {
  private cpu: CPU = new CPU();
  private memory: Memory = new Memory();
  private hardDrive: HardDrive = new HardDrive();
  
  start(): void {
    console.log('=== Starting Computer ===');
    this.cpu.freeze();
    this.memory.load(0, this.hardDrive.read(0, 1024));
    this.cpu.jump(0);
    this.cpu.execute();
    console.log('=== Computer Started ===');
  }
  shutdown(): void {
    console.log('=== Shutting Down Computer ===');
    console.log('CPU: Stopping...');
    console.log('Memory: Clearing...');
    console.log('HardDrive: Spinning down...');
    console.log('=== Computer Shutdown ===');
  }
}

export class HomeTheaterFacade {
  private amp: Amplifier = new Amplifier();
  private tuner: Tuner = new Tuner();
  private dvd: DVDPlayer = new DVDPlayer();
  private projector: Projector = new Projector();
  private lights: TheaterLights = new TheaterLights();
  private screen: Screen = new Screen();
  private popper: PopcornPopper = new PopcornPopper();
  
  watchMovie(movie: string): void {
    console.log('\n=== Get ready to watch a movie ===');
    this.popper.on(); this.popper.pop();
    this.lights.dim(10);
    this.screen.down();
    this.projector.on(); this.projector.setInput('DVD');
    this.amp.on(); this.amp.setVolume(5);
    this.dvd.on(); this.dvd.play(movie);
    console.log('=== Movie is playing ===');
  }
  endMovie(): void {
    console.log('\n=== Shutting movie theater down ===');
    this.popper.off(); this.lights.on(); this.screen.up();
    this.projector.off(); this.amp.off(); this.dvd.off();
    console.log('=== Movie theater shut down ===');
  }
  listenToRadio(frequency: number): void {
    console.log('\n=== Tuning in to radio ===');
    this.amp.on(); this.amp.setVolume(5);
    this.tuner.on(); this.tuner.setFrequency(frequency);
    console.log('=== Radio is playing ===');
  }
  turnOffRadio(): void {
    console.log('\n=== Shutting down radio ===');
    this.tuner.off(); this.amp.off();
    console.log('=== Radio turned off ===');
  }
}

export class OrderFacade {
  private inventory: InventorySystem = new InventorySystem();
  private payment: PaymentSystem = new PaymentSystem();
  private shipping: ShippingSystem = new ShippingSystem();
  private notification: NotificationSystem = new NotificationSystem();
  
  placeOrder(item: string, quantity: number, amount: number, address: string, email: string): boolean {
    console.log('\n=== Processing Order ===');
    if (!this.inventory.checkInventory(item, quantity)) {
      console.log('Order failed: Item not in stock');
      return false;
    }
    if (!this.payment.processPayment(amount)) {
      console.log('Order failed: Payment declined');
      return false;
    }
    this.inventory.updateInventory(item, -quantity);
    this.shipping.scheduleShipping(address);
    this.notification.sendConfirmation(email);
    console.log('=== Order Placed Successfully ===');
    return true;
  }
  cancelOrder(item: string, quantity: number, amount: number, email: string): void {
    console.log('\n=== Cancelling Order ===');
    this.inventory.updateInventory(item, quantity);
    this.payment.refundPayment(amount);
    this.shipping.cancelShipping();
    this.notification.sendCancellation(email);
    console.log('=== Order Cancelled ===');
  }
}
