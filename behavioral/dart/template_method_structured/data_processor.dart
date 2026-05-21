abstract class DataProcessor {
  void processData() {
    print('\n=== Starting Data Processing ===');
    readData();
    validateData();
    transformData();
    saveData();
    print('=== Data Processing Complete ===');
  }
  
  void readData();
  void validateData();
  void transformData();
  void saveData();
  
  void logProcessing() {
    print('Processing logged');
  }
}

class CSVDataProcessor extends DataProcessor {
  String _data = '';
  
  @override
  void readData() {
    print('Reading CSV file...');
    _data = 'name,age,city\nJohn,30,NYC\nJane,25,LA';
  }
  
  @override
  void validateData() {
    print('Validating CSV format...');
    print('CSV format is valid');
  }
  
  @override
  void transformData() {
    print('Transforming CSV to JSON...');
    _data = '[{"name":"John","age":30,"city":"NYC"},{"name":"Jane","age":25,"city":"LA"}]';
  }
  
  @override
  void saveData() {
    print('Saving JSON file...');
    print('Data saved: $_data');
  }
}

class XMLDataProcessor extends DataProcessor {
  String _data = '';
  
  @override
  void readData() {
    print('Reading XML file...');
    _data = '<users><user><name>John</name><age>30</age></user></users>';
  }
  
  @override
  void validateData() {
    print('Validating XML structure...');
    print('XML structure is valid');
  }
  
  @override
  void transformData() {
    print('Transforming XML to CSV...');
    _data = 'name,age\nJohn,30';
  }
  
  @override
  void saveData() {
    print('Saving CSV file...');
    print('Data saved: $_data');
  }
}
