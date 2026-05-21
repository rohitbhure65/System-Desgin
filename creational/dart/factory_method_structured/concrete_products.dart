import 'interfaces.dart';

class TextDocument extends Document {
  @override
  void open() => print('Opening Text Document in text editor...');
  @override
  void close() => print('Closing Text Document...');
  @override
  void save() => print('Saving Text Document as .txt file...');
  @override
  String get type => 'Text Document';
}

class PDFDocument extends Document {
  @override
  void open() => print('Opening PDF Document in PDF viewer...');
  @override
  void close() => print('Closing PDF Document...');
  @override
  void save() => print('Saving PDF Document as .pdf file...');
  @override
  String get type => 'PDF Document';
}

class HtmlDocument extends Document {
  @override
  void open() => print('Opening HTML Document in web browser...');
  @override
  void close() => print('Closing HTML Document...');
  @override
  void save() => print('Saving HTML Document as .html file...');
  @override
  String get type => 'HTML Document';
}

class CreditCardProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) => print('Processing credit card payment of \$$amount');
  @override
  void refundPayment(int amount) => print('Refunding credit card payment of \$$amount');
}

class PayPalProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) => print('Processing PayPal payment of \$$amount');
  @override
  void refundPayment(int amount) => print('Refunding PayPal payment of \$$amount');
}

class CryptoProcessor extends PaymentProcessor {
  @override
  void processPayment(int amount) => print('Processing cryptocurrency payment of \$$amount');
  @override
  void refundPayment(int amount) => print('Refunding cryptocurrency payment of \$$amount');
}
