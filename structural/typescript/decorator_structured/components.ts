export interface Coffee {
  getCost(): number;
  getDescription(): string;
}

export class SimpleCoffee implements Coffee {
  getCost(): number { return 2.0; }
  getDescription(): string { return 'Simple Coffee'; }
}

export interface TextComponent {
  getText(): string;
}

export class SimpleText implements TextComponent {
  constructor(private text: string) {}
  getText(): string { return this.text; }
}

export interface DataSource {
  writeData(data: string): void;
  readData(): string;
}

export class FileDataSource implements DataSource {
  private data: string = '';
  
  writeData(data: string): void {
    this.data = data;
    console.log(`Writing data to file: \${data}`);
  }
  
  readData(): string {
    console.log(`Reading data from file: \${this.data}`);
    return this.data;
  }
}
