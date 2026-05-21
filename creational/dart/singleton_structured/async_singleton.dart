class AsyncSingleton {
  static AsyncSingleton? _instance;
  static bool _isInitializing = false;
  
  AsyncSingleton._internal() {
    print('AsyncSingleton: Instance created');
  }

  static Future<AsyncSingleton> getInstance() async {
    if (_instance != null) return _instance!;

    while (_isInitializing) {
      await Future.delayed(Duration(milliseconds: 10));
      if (_instance != null) return _instance!;
    }

    _isInitializing = true;
    try {
      print('AsyncSingleton: Starting heavy async initialization...');
      await Future.delayed(Duration(milliseconds: 100));
      _instance = AsyncSingleton._internal();
    } finally {
      _isInitializing = false;
    }

    return _instance!;
  }
}
