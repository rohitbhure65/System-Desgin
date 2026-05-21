abstract class ReportGenerator {
  void generateReport() {
    print('\n=== Generating Report ===');
    collectData();
    analyzeData();
    formatReport();
    exportReport();
    print('=== Report Generated ===');
  }
  
  void collectData();
  void analyzeData();
  void formatReport();
  void exportReport();
}

class SalesReport extends ReportGenerator {
  @override
  void collectData() {
    print('Collecting sales data from database...');
  }
  
  @override
  void analyzeData() {
    print('Analyzing sales trends...');
    print('Sales increased by 15% this quarter');
  }
  
  @override
  void formatReport() {
    print('Formatting sales report with charts...');
  }
  
  @override
  void exportReport() {
    print('Exporting to PDF...');
  }
}

class InventoryReport extends ReportGenerator {
  @override
  void collectData() {
    print('Collecting inventory data...');
  }
  
  @override
  void analyzeData() {
    print('Analyzing stock levels...');
    print('3 items need restocking');
  }
  
  @override
  void formatReport() {
    print('Formatting inventory report with tables...');
  }
  
  @override
  void exportReport() {
    print('Exporting to Excel...');
  }
}
