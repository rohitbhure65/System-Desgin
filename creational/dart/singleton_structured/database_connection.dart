class DatabaseConnection {
  static DatabaseConnection? _instance;
  
  DatabaseConnection._internal() {
    print('DatabaseConnection: Initializing connection...');
    _isConnected = true;
  }
  
  factory DatabaseConnection() {
    _instance ??= DatabaseConnection._internal();
    return _instance!;
  }
  
  bool _isConnected = false;
  int _queryCount = 0;
  
  void executeQuery(String query) {
    if (_isConnected) {
      _queryCount++;
      print('Executing query #$_queryCount: $query');
    } else {
      print('Error: Not connected to database');
    }
  }
  
  int get queryCount => _queryCount;
  
  bool get connectionStatus => _isConnected;
}
