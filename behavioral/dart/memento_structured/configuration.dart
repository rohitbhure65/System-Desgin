class ConfigurationMemento {
  final String theme;
  final int fontSize;
  final bool notificationsEnabled;
  
  ConfigurationMemento(this.theme, this.fontSize, this.notificationsEnabled);
  
  String get getTheme => theme;
  int get getFontSize => fontSize;
  bool get getNotificationsEnabled => notificationsEnabled;
}

class ApplicationSettings {
  String _theme = 'light';
  int _fontSize = 12;
  bool _notificationsEnabled = true;
  
  void setTheme(String newTheme) {
    _theme = newTheme;
    print('Theme changed to $_theme');
  }
  
  void setFontSize(int size) {
    _fontSize = size;
    print('Font size set to $_fontSize');
  }
  
  void setNotificationsEnabled(bool enabled) {
    _notificationsEnabled = enabled;
    print('Notifications ${enabled ? "enabled" : "disabled"}');
  }
  
  void displaySettings() {
    print('=== Current Settings ===');
    print('Theme: $_theme');
    print('Font Size: $_fontSize');
    print('Notifications: ${_notificationsEnabled ? "Enabled" : "Disabled"}');
    print('=====================');
  }
  
  ConfigurationMemento saveConfiguration() {
    return ConfigurationMemento(_theme, _fontSize, _notificationsEnabled);
  }
  
  void restoreConfiguration(ConfigurationMemento memento) {
    _theme = memento.getTheme;
    _fontSize = memento.getFontSize;
    _notificationsEnabled = memento.getNotificationsEnabled;
    print('Configuration restored!');
    displaySettings();
  }
}
