abstract class Document {
  void open();
  void close();
  void save();
  String get type;
}

abstract class DocumentApplication {
  Document createDocument();
  
  void newDocument() {
    var doc = createDocument();
    print('Created: ${doc.type}');
    doc.open();
    doc.save();
    doc.close();
  }
}

abstract class PaymentProcessor {
  void processPayment(int amount);
  void refundPayment(int amount);
}
