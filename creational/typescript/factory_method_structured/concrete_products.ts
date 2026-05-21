import { Document, PaymentProcessor } from './interfaces';

export class TextDocument implements Document {
  open(): void { console.log('Opening Text Document in text editor...'); }
  close(): void { console.log('Closing Text Document...'); }
  save(): void { console.log('Saving Text Document as .txt file...'); }
  getType(): string { return 'Text Document'; }
}

export class PDFDocument implements Document {
  open(): void { console.log('Opening PDF Document in PDF viewer...'); }
  close(): void { console.log('Closing PDF Document...'); }
  save(): void { console.log('Saving PDF Document as .pdf file...'); }
  getType(): string { return 'PDF Document'; }
}

export class HtmlDocument implements Document {
  open(): void { console.log('Opening HTML Document in web browser...'); }
  close(): void { console.log('Closing HTML Document...'); }
  save(): void { console.log('Saving HTML Document as .html file...'); }
  getType(): string { return 'HTML Document'; }
}

export class CreditCardProcessor implements PaymentProcessor {
  processPayment(amount: number): void { console.log(`Processing credit card payment of $${amount}`); }
  refundPayment(amount: number): void { console.log(`Refunding credit card payment of $${amount}`); }
}

export class PayPalProcessor implements PaymentProcessor {
  processPayment(amount: number): void { console.log(`Processing PayPal payment of $${amount}`); }
  refundPayment(amount: number): void { console.log(`Refunding PayPal payment of $${amount}`); }
}

export class CryptoProcessor implements PaymentProcessor {
  processPayment(amount: number): void { console.log(`Processing cryptocurrency payment of $${amount}`); }
  refundPayment(amount: number): void { console.log(`Refunding cryptocurrency payment of $${amount}`); }
}
