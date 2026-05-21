import { Coffee, TextComponent, DataSource, SimpleCoffee, SimpleText, FileDataSource } from './components';
import { MilkDecorator, SugarDecorator, WhippedCreamDecorator, BoldDecorator, ItalicDecorator, UnderlineDecorator, EncryptionDecorator, CompressionDecorator } from './decorators';

function demoDecorator(): void {
  console.log('=== Decorator Pattern Demo ===\n');
  
  console.log('--- Coffee Shop Example ---');
  let coffee: Coffee = new SimpleCoffee();
  console.log(`\${coffee.getDescription()} $\${coffee.getCost()}`);
  
  coffee = new MilkDecorator(coffee);
  console.log(`\${coffee.getDescription()} $\${coffee.getCost()}`);
  coffee = new SugarDecorator(coffee);
  console.log(`\${coffee.getDescription()} $\${coffee.getCost()}`);
  coffee = new WhippedCreamDecorator(coffee);
  console.log(`\${coffee.getDescription()} $\${coffee.getCost()}`);
  console.log();
  
  console.log('--- Text Formatting Example ---');
  let text: TextComponent = new SimpleText('Hello World');
  console.log(`Original: \${text.getText()}`);
  
  text = new BoldDecorator(text);
  console.log(`Bold: \${text.getText()}`);
  text = new ItalicDecorator(text);
  console.log(`Bold + Italic: \${text.getText()}`);
  text = new UnderlineDecorator(text);
  console.log(`Bold + Italic + Underline: \${text.getText()}`);
  console.log();
  
  console.log('--- Data Stream Processing Example ---');
  let dataSource: DataSource = new FileDataSource();
  console.log('\nWriting plain data:');
  dataSource.writeData('Important Data');
  console.log(`Reading: \${dataSource.readData()}`);
  
  console.log('\nWriting encrypted data:');
  dataSource = new EncryptionDecorator(dataSource);
  dataSource.writeData('Secret Data');
  console.log(`Reading: \${dataSource.readData()}`);
  
  console.log('\nWriting encrypted and compressed data:');
  dataSource = new CompressionDecorator(dataSource);
  dataSource.writeData('Very Secret Data');
  console.log(`Reading: \${dataSource.readData()}`);
}

demoDecorator();
