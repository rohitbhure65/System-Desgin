export abstract class DataProcessor {
  processData(): void {
    console.log('\n=== Starting Data Processing ===');
    this.readData();
    this.validateData();
    this.transformData();
    this.saveData();
    console.log('=== Data Processing Complete ===');
  }
  
  protected abstract readData(): void;
  protected abstract validateData(): void;
  protected abstract transformData(): void;
  protected abstract saveData(): void;
  
  protected logProcessing(): void {
    console.log('Processing logged');
  }
}

export class CSVDataProcessor extends DataProcessor {
  private data: string = '';
  
  protected readData(): void {
    console.log('Reading CSV file...');
    this.data = 'name,age,city\nJohn,30,NYC\nJane,25,LA';
  }
  
  protected validateData(): void {
    console.log('Validating CSV format...');
    console.log('CSV format is valid');
  }
  
  protected transformData(): void {
    console.log('Transforming CSV to JSON...');
    this.data = '[{"name":"John","age":30,"city":"NYC"},{"name":"Jane","age":25,"city":"LA"}]';
  }
  
  protected saveData(): void {
    console.log('Saving JSON file...');
    console.log(`Data saved: ${this.data}`);
  }
}

export class XMLDataProcessor extends DataProcessor {
  private data: string = '';
  
  protected readData(): void {
    console.log('Reading XML file...');
    this.data = '<users><user><name>John</name><age>30</age></user></users>';
  }
  
  protected validateData(): void {
    console.log('Validating XML structure...');
    console.log('XML structure is valid');
  }
  
  protected transformData(): void {
    console.log('Transforming XML to CSV...');
    this.data = 'name,age\nJohn,30';
  }
  
  protected saveData(): void {
    console.log('Saving CSV file...');
    console.log(`Data saved: ${this.data}`);
  }
}
