import 'components.dart';
import 'decorators.dart';

void main() {
  print('=== Decorator Pattern Demo ===\n');
  
  print('--- Coffee Shop Example ---');
  Coffee coffee = SimpleCoffee();
  print('\${coffee.getDescription()} \$\${coffee.getCost()}');
  
  coffee = MilkDecorator(coffee);
  print('\${coffee.getDescription()} \$\${coffee.getCost()}');
  coffee = SugarDecorator(coffee);
  print('\${coffee.getDescription()} \$\${coffee.getCost()}');
  coffee = WhippedCreamDecorator(coffee);
  print('\${coffee.getDescription()} \$\${coffee.getCost()}');
  print('');
  
  print('--- Text Formatting Example ---');
  TextComponent text = SimpleText('Hello World');
  print('Original: \${text.getText()}');
  text = BoldDecorator(text);
  print('Bold: \${text.getText()}');
  text = ItalicDecorator(text);
  print('Bold + Italic: \${text.getText()}');
  text = UnderlineDecorator(text);
  print('Bold + Italic + Underline: \${text.getText()}');
  print('');
  
  print('--- Data Stream Processing Example ---');
  DataSource dataSource = FileDataSource();
  print('\nWriting plain data:');
  dataSource.writeData('Important Data');
  print('Reading: \${dataSource.readData()}');
  
  print('\nWriting encrypted data:');
  dataSource = EncryptionDecorator(dataSource);
  dataSource.writeData('Secret Data');
  print('Reading: \${dataSource.readData()}');
  
  print('\nWriting encrypted and compressed data:');
  dataSource = CompressionDecorator(dataSource);
  dataSource.writeData('Very Secret Data');
  print('Reading: \${dataSource.readData()}');
}
