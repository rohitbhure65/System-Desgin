import 'components.dart';

abstract class CoffeeDecorator extends Coffee {
  final Coffee decoratedCoffee;
  CoffeeDecorator(this.decoratedCoffee);
  @override
  double getCost() { return decoratedCoffee.getCost(); }
  @override
  String getDescription() { return decoratedCoffee.getDescription(); }
}

class MilkDecorator extends CoffeeDecorator {
  MilkDecorator(super.coffee);
  @override
  double getCost() { return super.getCost() + 0.5; }
  @override
  String getDescription() { return '\${super.getDescription()}, Milk'; }
}

class SugarDecorator extends CoffeeDecorator {
  SugarDecorator(super.coffee);
  @override
  double getCost() { return super.getCost() + 0.2; }
  @override
  String getDescription() { return '\${super.getDescription()}, Sugar'; }
}

class WhippedCreamDecorator extends CoffeeDecorator {
  WhippedCreamDecorator(super.coffee);
  @override
  double getCost() { return super.getCost() + 1.0; }
  @override
  String getDescription() { return '\${super.getDescription()}, Whipped Cream'; }
}

abstract class TextDecorator extends TextComponent {
  final TextComponent wrappedText;
  TextDecorator(this.wrappedText);
  @override
  String getText() { return wrappedText.getText(); }
}

class BoldDecorator extends TextDecorator {
  BoldDecorator(super.text);
  @override
  String getText() { return '<b>\${super.getText()}</b>'; }
}

class ItalicDecorator extends TextDecorator {
  ItalicDecorator(super.text);
  @override
  String getText() { return '<i>\${super.getText()}</i>'; }
}

class UnderlineDecorator extends TextDecorator {
  UnderlineDecorator(super.text);
  @override
  String getText() { return '<u>\${super.getText()}</u>'; }
}

abstract class DataSourceDecorator extends DataSource {
  final DataSource wrappedSource;
  DataSourceDecorator(this.wrappedSource);
  @override
  void writeData(String data) { wrappedSource.writeData(data); }
  @override
  String readData() { return wrappedSource.readData(); }
}

class EncryptionDecorator extends DataSourceDecorator {
  EncryptionDecorator(super.source);
  @override
  void writeData(String data) {
    var encrypted = '[ENCRYPTED]\$data[ENCRYPTED]';
    print('Encrypting data...');
    wrappedSource.writeData(encrypted);
  }
  @override
  String readData() {
    var data = wrappedSource.readData();
    print('Decrypting data...');
    if (data.startsWith('[ENCRYPTED]')) {
      return data.substring(11, data.length - 11);
    }
    return data;
  }
}

class CompressionDecorator extends DataSourceDecorator {
  CompressionDecorator(super.source);
  @override
  void writeData(String data) {
    var compressed = '[COMPRESSED]\$data[COMPRESSED]';
    print('Compressing data...');
    wrappedSource.writeData(compressed);
  }
  @override
  String readData() {
    var data = wrappedSource.readData();
    print('Decompressing data...');
    if (data.startsWith('[COMPRESSED]')) {
      return data.substring(12, data.length - 12);
    }
    return data;
  }
}
