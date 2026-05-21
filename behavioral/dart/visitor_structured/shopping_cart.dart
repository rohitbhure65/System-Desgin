import 'interfaces.dart';

class Book extends Item {
  final String _title;
  final String _author;
  final double _price;
  
  Book(this._title, this._author, this._price);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitBook(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get title => _title;
  String get author => _author;
}

class Fruit extends Item {
  final String _name;
  final double _price;
  final double _weight;
  
  Fruit(this._name, this._price, this._weight);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitFruit(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get name => _name;
  double get weight => _weight;
}

class Electronic extends Item {
  final String _model;
  final String _brand;
  final double _price;
  
  Electronic(this._brand, this._model, this._price);
  
  @override
  void accept(Visitor visitor) {
    visitor.visitElectronic(this);
  }
  
  @override
  double getPrice() => _price;
  
  String get model => _model;
  String get brand => _brand;
}

class PriceCalculator implements Visitor {
  double _totalPrice = 0;
  
  @override
  void visitBook(Book book) {
    _totalPrice += book.getPrice();
    print('Book: ${book.title} - \$${book.getPrice()}');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    _totalPrice += fruit.getPrice();
    print('Fruit: ${fruit.name} - \$${fruit.getPrice()}');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    _totalPrice += electronic.getPrice();
    print('Electronic: ${electronic.brand} ${electronic.model} - \$${electronic.getPrice()}');
  }
  
  double get totalPrice => _totalPrice;
}

class DescriptionGenerator implements Visitor {
  @override
  void visitBook(Book book) {
    print('Book: "${book.title}" by ${book.author} - A great read!');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    print('Fruit: ${fruit.name} (${fruit.weight}kg) - Fresh and healthy!');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    print('Electronic: ${electronic.brand} ${electronic.model} - High-tech gadget!');
  }
}

class TaxCalculator implements Visitor {
  double _totalTax = 0;
  
  @override
  void visitBook(Book book) {
    final tax = book.getPrice() * 0.05;
    _totalTax += tax;
    print('Book tax: \$${tax}');
  }
  
  @override
  void visitFruit(Fruit fruit) {
    final tax = fruit.getPrice() * 0.02;
    _totalTax += tax;
    print('Fruit tax: \$${tax}');
  }
  
  @override
  void visitElectronic(Electronic electronic) {
    final tax = electronic.getPrice() * 0.10;
    _totalTax += tax;
    print('Electronic tax: \$${tax}');
  }
  
  double get totalTax => _totalTax;
}

class ShoppingCart {
  final List<Item> _items = [];
  
  void addItem(Item item) {
    _items.add(item);
  }
  
  void acceptVisitor(Visitor visitor) {
    for (final item in _items) {
      item.accept(visitor);
    }
  }
}
