export class Light {
  on(): void {
    console.log('Light is ON');
  }
  
  off(): void {
    console.log('Light is OFF');
  }
}

export class Stereo {
  on(): void {
    console.log('Stereo is ON');
  }
  
  off(): void {
    console.log('Stereo is OFF');
  }
  
  setVolume(level: number): void {
    console.log(`Stereo volume set to ${level}`);
  }
}

export class BankAccount {
  private balance: number;
  
  constructor(initialBalance: number = 0) {
    this.balance = initialBalance;
  }
  
  deposit(amount: number): void {
    this.balance += amount;
    console.log(`Deposited $${amount}. New balance: $${this.balance}`);
  }
  
  withdraw(amount: number): void {
    if (this.balance >= amount) {
      this.balance -= amount;
      console.log(`Withdrew $${amount}. New balance: $${this.balance}`);
    } else {
      console.log('Insufficient funds');
    }
  }
  
  getBalance(): number {
    return this.balance;
  }
}
