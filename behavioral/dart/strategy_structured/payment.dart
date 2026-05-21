import 'interfaces.dart';

class CreditCardPayment implements PaymentStrategy {
  final String _cardNumber;
  final String _expiryDate;
  
  CreditCardPayment(this._cardNumber, this._expiryDate);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with Credit Card ending in ${_cardNumber.substring(_cardNumber.length - 4)}');
    print('  Card: ****-****-****-${_cardNumber.substring(_cardNumber.length - 4)}');
    print('  Expiry: $_expiryDate');
  }
}

class PayPalPayment implements PaymentStrategy {
  final String _email;
  
  PayPalPayment(this._email);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with PayPal');
    print('  Account: $_email');
  }
}

class CryptoPayment implements PaymentStrategy {
  final String _walletAddress;
  
  CryptoPayment(this._walletAddress);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with Cryptocurrency');
    print('  Wallet: ${_walletAddress.substring(0, 10)}...');
  }
}

class ShoppingCart {
  PaymentStrategy? _paymentStrategy;
  final List<_Item> _items = [];
  
  void setPaymentStrategy(PaymentStrategy strategy) {
    _paymentStrategy = strategy;
  }
  
  void addItem(String item, double price) {
    _items.add(_Item(item, price));
  }
  
  double getTotal() {
    return _items.fold(0, (total, item) => total + item.price);
  }
  
  void checkout() {
    print('\n=== Checkout ===');
    print('Items:');
    for (final item in _items) {
      print('  - ${item.name}: \$${item.price}');
    }
    print('Total: \$${getTotal()}');
    
    if (_paymentStrategy != null) {
      _paymentStrategy!.pay(getTotal());
    } else {
      print('No payment method selected');
    }
  }
}

class _Item {
  final String name;
  final double price;
  
  _Item(this.name, this.price);
}
