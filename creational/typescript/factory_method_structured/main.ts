import { TextEditor, PDFViewer, WebBrowser, DocumentFactory, DocType, PaymentFactory, PaymentMethod } from './creators';

function demoFactoryMethod(): void {
  console.log('=== Factory Method Pattern Demo ===\n');
  
  console.log('--- Inheritance-based Factory Method ---');
  
  const textEditor = new TextEditor();
  textEditor.newDocument();
  console.log('');
  
  const pdfViewer = new PDFViewer();
  pdfViewer.newDocument();
  console.log('');
  
  const webBrowser = new WebBrowser();
  webBrowser.newDocument();
  console.log('');
  
  console.log('--- Parameterized Factory Method ---');
  
  const textDoc = DocumentFactory.createDocument(DocType.text);
  textDoc.open();
  console.log('');
  
  const pdfDoc = DocumentFactory.createDocument(DocType.pdf);
  pdfDoc.open();
  console.log('');
  
  const htmlDoc = DocumentFactory.createDocument(DocType.html);
  htmlDoc.open();
  console.log('');
  
  console.log('--- Payment Processing Example ---');
  
  const creditCardProcessor = PaymentFactory.createProcessor(PaymentMethod.creditCard);
  creditCardProcessor.processPayment(100);
  creditCardProcessor.refundPayment(50);
  console.log('');
  
  const payPalProcessor = PaymentFactory.createProcessor(PaymentMethod.payPal);
  payPalProcessor.processPayment(75);
  console.log('');
  
  const cryptoProcessor = PaymentFactory.createProcessor(PaymentMethod.crypto);
  cryptoProcessor.processPayment(200);
}

demoFactoryMethod();
