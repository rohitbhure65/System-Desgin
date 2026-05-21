import { Command } from './interfaces';
import { Light, Stereo, BankAccount } from './receivers';

export class LightOnCommand implements Command {
  private light: Light;
  
  constructor(light: Light) {
    this.light = light;
  }
  
  execute(): void {
    this.light.on();
  }
  
  undo(): void {
    this.light.off();
  }
}

export class LightOffCommand implements Command {
  private light: Light;
  
  constructor(light: Light) {
    this.light = light;
  }
  
  execute(): void {
    this.light.off();
  }
  
  undo(): void {
    this.light.on();
  }
}

export class StereoOnCommand implements Command {
  private stereo: Stereo;
  private previousVolume: number = 0;
  
  constructor(stereo: Stereo) {
    this.stereo = stereo;
  }
  
  execute(): void {
    this.stereo.on();
    this.stereo.setVolume(10);
    this.previousVolume = 10;
  }
  
  undo(): void {
    this.stereo.setVolume(this.previousVolume);
    this.stereo.off();
  }
}

export class StereoOffCommand implements Command {
  private stereo: Stereo;
  
  constructor(stereo: Stereo) {
    this.stereo = stereo;
  }
  
  execute(): void {
    this.stereo.off();
  }
  
  undo(): void {
    this.stereo.on();
  }
}

export class DepositCommand implements Command {
  private account: BankAccount;
  private amount: number;
  
  constructor(account: BankAccount, amount: number) {
    this.account = account;
    this.amount = amount;
  }
  
  execute(): void {
    this.account.deposit(this.amount);
  }
  
  undo(): void {
    this.account.withdraw(this.amount);
  }
}

export class WithdrawCommand implements Command {
  private account: BankAccount;
  private amount: number;
  private success: boolean = false;
  
  constructor(account: BankAccount, amount: number) {
    this.account = account;
    this.amount = amount;
  }
  
  execute(): void {
    const oldBalance = this.account.getBalance();
    this.account.withdraw(this.amount);
    this.success = this.account.getBalance() < oldBalance;
  }
  
  undo(): void {
    if (this.success) {
      this.account.deposit(this.amount);
    }
  }
}
