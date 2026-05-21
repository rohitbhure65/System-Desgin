import { State } from './interfaces';

export class VendingMachine {
  private currentState: State;
  private coinCount: number = 0;
  private stockCount: number;
  
  constructor(initialStock: number) {
    this.stockCount = initialStock;
    if (initialStock > 0) {
      this.currentState = new NoCoinState(this);
    } else {
      this.currentState = new SoldOutState(this);
    }
  }
  
  setState(state: State): void {
    this.currentState = state;
  }
  
  insertCoin(): void {
    this.currentState.insertCoin();
  }
  
  ejectCoin(): void {
    this.currentState.ejectCoin();
  }
  
  pressButton(): void {
    this.currentState.pressButton();
  }
  
  dispense(): void {
    this.currentState.dispense();
  }
  
  addCoin(): void {
    this.coinCount++;
    console.log(`Coin inserted. Total coins: ${this.coinCount}`);
  }
  
  returnCoin(): void {
    if (this.coinCount > 0) {
      this.coinCount--;
      console.log(`Coin returned. Total coins: ${this.coinCount}`);
    }
  }
  
  releaseProduct(): void {
    if (this.stockCount > 0) {
      this.stockCount--;
      this.coinCount--;
      console.log(`Product dispensed. Stock: ${this.stockCount}, Coins: ${this.coinCount}`);
    }
  }
  
  getCoinCount(): number {
    return this.coinCount;
  }
  
  getStockCount(): number {
    return this.stockCount;
  }
}

export class NoCoinState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Coin inserted...');
    this.machine.addCoin();
    this.machine.setState(new HasCoinState(this.machine));
  }
  
  ejectCoin(): void {
    console.log('No coin to eject');
  }
  
  pressButton(): void {
    console.log('Please insert a coin first');
  }
  
  dispense(): void {
    console.log('Please insert a coin first');
  }
}

export class HasCoinState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Coin already inserted');
  }
  
  ejectCoin(): void {
    console.log('Coin ejected');
    this.machine.returnCoin();
    this.machine.setState(new NoCoinState(this.machine));
  }
  
  pressButton(): void {
    console.log('Button pressed...');
    if (this.machine.getStockCount() > 0) {
      this.machine.setState(new DispensingState(this.machine));
      this.machine.dispense();
    } else {
      console.log('Out of stock');
      this.machine.setState(new SoldOutState(this.machine));
    }
  }
  
  dispense(): void {
    console.log('Press button to dispense');
  }
}

export class DispensingState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Please wait, dispensing...');
  }
  
  ejectCoin(): void {
    console.log('Cannot eject during dispensing');
  }
  
  pressButton(): void {
    console.log('Already dispensing...');
  }
  
  dispense(): void {
    this.machine.releaseProduct();
    if (this.machine.getStockCount() > 0) {
      this.machine.setState(new NoCoinState(this.machine));
    } else {
      this.machine.setState(new SoldOutState(this.machine));
    }
  }
}

export class SoldOutState implements State {
  private machine: VendingMachine;
  
  constructor(machine: VendingMachine) {
    this.machine = machine;
  }
  
  insertCoin(): void {
    console.log('Cannot insert coin, machine is sold out');
  }
  
  ejectCoin(): void {
    console.log('Cannot eject, no coin inserted');
  }
  
  pressButton(): void {
    console.log('Machine is sold out');
  }
  
  dispense(): void {
    console.log('Machine is sold out');
  }
}
