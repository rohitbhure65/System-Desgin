export abstract class ReportGenerator {
  generateReport(): void {
    console.log('\n=== Generating Report ===');
    this.collectData();
    this.analyzeData();
    this.formatReport();
    this.exportReport();
    console.log('=== Report Generated ===');
  }
  
  protected abstract collectData(): void;
  protected abstract analyzeData(): void;
  protected abstract formatReport(): void;
  protected abstract exportReport(): void;
}

export class SalesReport extends ReportGenerator {
  protected collectData(): void {
    console.log('Collecting sales data from database...');
  }
  
  protected analyzeData(): void {
    console.log('Analyzing sales trends...');
    console.log('Sales increased by 15% this quarter');
  }
  
  protected formatReport(): void {
    console.log('Formatting sales report with charts...');
  }
  
  protected exportReport(): void {
    console.log('Exporting to PDF...');
  }
}

export class InventoryReport extends ReportGenerator {
  protected collectData(): void {
    console.log('Collecting inventory data...');
  }
  
  protected analyzeData(): void {
    console.log('Analyzing stock levels...');
    console.log('3 items need restocking');
  }
  
  protected formatReport(): void {
    console.log('Formatting inventory report with tables...');
  }
  
  protected exportReport(): void {
    console.log('Exporting to Excel...');
  }
}
