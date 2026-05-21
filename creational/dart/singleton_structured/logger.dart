class Logger {
  static Logger? _instance;
  
  Logger._() {
    print('Logger: Initializing logger...');
  }
  
  static Logger get instance {
    _instance ??= Logger._();
    return _instance!;
  }
  
  int _logCount = 0;
  
  void log(String message) {
    _logCount++;
    print('[LOG #$_logCount] $message');
  }
  
  int get logCount => _logCount;
}
