import 'creators.dart';

void main() {
  print('=== Factory Method Pattern Demo ===\n');
  
  // Using inheritance-based Factory Method
  print('--- Inheritance-based Factory Method ---');
  
  var textEditor = TextEditor();
  textEditor.newDocument();
  print('');
  
  var pdfViewer = PDFViewer();
  pdfViewer.newDocument();
  print('');
  
  var webBrowser = WebBrowser();
  webBrowser.newDocument();
  print('');
  
  // Using parameterized Factory Method
  print('--- Parameterized Factory Method ---');
  
  var textDoc = DocumentFactory.createDocument(DocType.text);
  textDoc.open();
  print('');
  
  var pdfDoc = DocumentFactory.createDocument(DocType.pdf);
  pdfDoc.open();
  print('');
  
  var htmlDoc = DocumentFactory.createDocument(DocType.html);
  htmlDoc.open();
  print('');
  
  // Payment Processing Example
  print('--- Payment Processing Example ---');
  
  var creditCardProcessor = PaymentFactory.createProcessor(PaymentMethod.creditCard);
  creditCardProcessor.processPayment(100);
  creditCardProcessor.refundPayment(50);
  print('');
  
  var payPalProcessor = PaymentFactory.createProcessor(PaymentMethod.payPal);
  payPalProcessor.processPayment(75);
  print('');
  
  var cryptoProcessor = PaymentFactory.createProcessor(PaymentMethod.crypto);
  cryptoProcessor.processPayment(200);
}
