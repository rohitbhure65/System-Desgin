import { Coffee, TextComponent, DataSource } from './components';

export abstract class CoffeeDecorator implements Coffee {
  protected decoratedCoffee: Coffee;
  constructor(coffee: Coffee) { this.decoratedCoffee = coffee; }
  getCost(): number { return this.decoratedCoffee.getCost(); }
  getDescription(): string { return this.decoratedCoffee.getDescription(); }
}

export class MilkDecorator extends CoffeeDecorator {
  getCost(): number { return super.getCost() + 0.5; }
  getDescription(): string { return super.getDescription() + ', Milk'; }
}

export class SugarDecorator extends CoffeeDecorator {
  getCost(): number { return super.getCost() + 0.2; }
  getDescription(): string { return super.getDescription() + ', Sugar'; }
}

export class WhippedCreamDecorator extends CoffeeDecorator {
  getCost(): number { return super.getCost() + 1.0; }
  getDescription(): string { return super.getDescription() + ', Whipped Cream'; }
}

export abstract class TextDecorator implements TextComponent {
  protected wrappedText: TextComponent;
  constructor(text: TextComponent) { this.wrappedText = text; }
  getText(): string { return this.wrappedText.getText(); }
}

export class BoldDecorator extends TextDecorator {
  getText(): string { return `<b>\${super.getText()}</b>`; }
}

export class ItalicDecorator extends TextDecorator {
  getText(): string { return `<i>\${super.getText()}</i>`; }
}

export class UnderlineDecorator extends TextDecorator {
  getText(): string { return `<u>\${super.getText()}</u>`; }
}

export abstract class DataSourceDecorator implements DataSource {
  protected wrappedSource: DataSource;
  constructor(source: DataSource) { this.wrappedSource = source; }
  writeData(data: string): void { this.wrappedSource.writeData(data); }
  readData(): string { return this.wrappedSource.readData(); }
}

export class EncryptionDecorator extends DataSourceDecorator {
  writeData(data: string): void {
    const encrypted = `[ENCRYPTED]\${data}[ENCRYPTED]`;
    console.log('Encrypting data...');
    this.wrappedSource.writeData(encrypted);
  }
  readData(): string {
    const data = this.wrappedSource.readData();
    console.log('Decrypting data...');
    if (data.startsWith('[ENCRYPTED]')) {
      return data.substring(11, data.length - 11);
    }
    return data;
  }
}

export class CompressionDecorator extends DataSourceDecorator {
  writeData(data: string): void {
    const compressed = `[COMPRESSED]\${data}[COMPRESSED]`;
    console.log('Compressing data...');
    this.wrappedSource.writeData(compressed);
  }
  readData(): string {
    const data = this.wrappedSource.readData();
    console.log('Decompressing data...');
    if (data.startsWith('[COMPRESSED]')) {
      return data.substring(12, data.length - 12);
    }
    return data;
  }
}
