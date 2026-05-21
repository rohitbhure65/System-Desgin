import { Application, Document, PaymentProcessor } from './interfaces';
import { TextDocument, PDFDocument, HtmlDocument, CreditCardProcessor, PayPalProcessor, CryptoProcessor } from './concrete_products';

export class TextEditor extends Application {
  protected createDocument(): Document { return new TextDocument(); }
}

export class PDFViewer extends Application {
  protected createDocument(): Document { return new PDFDocument(); }
}

export class WebBrowser extends Application {
  protected createDocument(): Document { return new HtmlDocument(); }
}

export enum DocType { text, pdf, html }

export class DocumentFactory {
  static createDocument(type: DocType): Document {
    switch (type) {
      case DocType.text: return new TextDocument();
      case DocType.pdf: return new PDFDocument();
      case DocType.html: return new HtmlDocument();
    }
  }
}

export enum PaymentMethod { creditCard, payPal, crypto }

export class PaymentFactory {
  static createProcessor(method: PaymentMethod): PaymentProcessor {
    switch (method) {
      case PaymentMethod.creditCard: return new CreditCardProcessor();
      case PaymentMethod.payPal: return new PayPalProcessor();
      case PaymentMethod.crypto: return new CryptoProcessor();
    }
  }
}
