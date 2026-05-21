export interface Document {
  open(): void;
  close(): void;
  save(): void;
  getType(): string;
}

export abstract class Application {
  protected abstract createDocument(): Document;
  
  public newDocument(): void {
    const doc = this.createDocument();
    console.log(`Created: ${doc.getType()}`);
    doc.open();
    doc.save();
    doc.close();
  }
}

export interface PaymentProcessor {
  processPayment(amount: number): void;
  refundPayment(amount: number): void;
}
