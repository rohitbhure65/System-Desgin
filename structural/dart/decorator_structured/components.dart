abstract class Coffee {
  double getCost();
  String getDescription();
}

class SimpleCoffee extends Coffee {
  @override
  double getCost() { return 2.0; }
  @override
  String getDescription() { return 'Simple Coffee'; }
}

abstract class TextComponent {
  String getText();
}

class SimpleText extends TextComponent {
  final String text;
  SimpleText(this.text);
  @override
  String getText() { return text; }
}

abstract class DataSource {
  void writeData(String data);
  String readData();
}

class FileDataSource extends DataSource {
  String _data = '';
  @override
  void writeData(String data) {
    _data = data;
    print('Writing data to file: \$data');
  }
  @override
  String readData() {
    print('Reading data from file: \$_data');
    return _data;
  }
}
