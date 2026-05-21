class ConfigurationManager {
  static ConfigurationManager? _instance;
  
  final Map<String, String> _config = {};
  
  ConfigurationManager._({Map<String, String>? initialConfig}) {
    print('ConfigurationManager: Initializing...');
    if (initialConfig != null) {
      _config.addAll(initialConfig);
    }
  }
  
  static ConfigurationManager getInstance({Map<String, String>? initialConfig}) {
    _instance ??= ConfigurationManager._(initialConfig: initialConfig);
    return _instance!;
  }
  
  void set(String key, String value) {
    _config[key] = value;
  }
  
  String? get(String key) {
    return _config[key];
  }
  
  void displayConfig() {
    print('Current Configuration:');
    _config.forEach((key, value) {
      print('  $key: $value');
    });
  }
}
