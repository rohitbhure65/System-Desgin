import { PaymentStrategy } from './interfaces';

export class CreditCardPayment implements PaymentStrategy {
  private cardNumber: string;
  private expiryDate: string;
  private cvv: string;
  
  constructor(card: string, expiry: string, cvv: string) {
    this.cardNumber = card;
    this.expiryDate = expiry;
    this.cvv = cvv;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with Credit Card ending in ${this.cardNumber.slice(-4)}`);
    console.log(`  Card: ****-****-****-${this.cardNumber.slice(-4)}`);
    console.log(`  Expiry: ${this.expiryDate}`);
  }
}

export class PayPalPayment implements PaymentStrategy {
  private email: string;
  private password: string;
  
  constructor(email: string, password: string) {
    this.email = email;
    this.password = password;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with PayPal`);
    console.log(`  Account: ${this.email}`);
  }
}

export class CryptoPayment implements PaymentStrategy {
  private walletAddress: string;
  private privateKey: string;
  
  constructor(wallet: string, key: string) {
    this.walletAddress = wallet;
    this.privateKey = key;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with Cryptocurrency`);
    console.log(`  Wallet: ${this.walletAddress.slice(0, 10)}...`);
  }
}

export class ShoppingCart {
  private paymentStrategy: PaymentStrategy | null = null;
  private items: { name: string; price: number }[] = [];
  
  setPaymentStrategy(strategy: PaymentStrategy): void {
    this.paymentStrategy = strategy;
  }
  
  addItem(item: string, price: number): void {
    this.items.push({ name: item, price: price });
  }
  
  getTotal(): number {
    return this.items.reduce((total, item) => total + item.price, 0);
  }
  
  checkout(): void {
    console.log('\n=== Checkout ===');
    console.log('Items:');
    for (const item of this.items) {
      console.log(`  - ${item.name}: $${item.price}`);
    }
    console.log(`Total: $${this.getTotal()}`);
    
    if (this.paymentStrategy) {
      this.paymentStrategy.pay(this.getTotal());
    } else {
      console.log('No payment method selected');
    }
  }
}
