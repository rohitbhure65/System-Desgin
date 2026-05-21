import 'interfaces.dart';
import 'concrete_products.dart';

class TextEditor extends DocumentApplication {
  @override
  Document createDocument() {
    return TextDocument();
  }
}

class PDFViewer extends DocumentApplication {
  @override
  Document createDocument() {
    return PDFDocument();
  }
}

class WebBrowser extends DocumentApplication {
  @override
  Document createDocument() {
    return HtmlDocument();
  }
}

enum DocType { text, pdf, html }

class DocumentFactory {
  static Document createDocument(DocType type) {
    switch (type) {
      case DocType.text:
        return TextDocument();
      case DocType.pdf:
        return PDFDocument();
      case DocType.html:
        return HtmlDocument();
    }
  }
}

enum PaymentMethod { creditCard, payPal, crypto }

class PaymentFactory {
  static PaymentProcessor createProcessor(PaymentMethod method) {
    switch (method) {
      case PaymentMethod.creditCard:
        return CreditCardProcessor();
      case PaymentMethod.payPal:
        return PayPalProcessor();
      case PaymentMethod.crypto:
        return CryptoProcessor();
    }
  }
}
