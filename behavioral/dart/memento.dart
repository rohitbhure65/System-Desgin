/*
 * MEMENTO DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Memento pattern lets you save and restore the previous state of an object without revealing the details of its implementation.
 * It provides the ability to restore an object to its previous state (undo).
 * 
 * WHY DOES IT EXIST?
 * - When you need to implement undo/redo functionality
 * - When you want to create snapshots of an object's state
 * - When direct access to the object's internal representation would violate encapsulation
 * 
 * WHEN TO USE IT?
 * - When you need to save and restore the state of an object without exposing its internal structure
 * - When you want to implement undo/redo operations
 * - When you need to maintain a history of states
 * - Common use cases: text editors (undo/redo), game states, database transactions, configuration management
 * 
 * PROS:
 * - Preserves encapsulation (doesn't expose internal state)
 * - Simplifies the originator (doesn't need to manage state history)
 * - Can provide snapshots at different times
 * - Supports undo/redo functionality
 * 
 * CONS:
 * - Can be expensive if the originator has large state
 * - May consume significant memory if many mementos are stored
 * - Caretaker must track the originator's lifecycle
 * - Can be complex to implement for complex objects
 * 
 * REAL-WORLD ANALOGY:
 * Think of a game save system. When you save a game, the game creates a snapshot of your current state (position, health, inventory). This snapshot (memento) is stored separately. Later, you can restore the game to that exact state by loading the snapshot. The game doesn't need to know how the snapshot is stored, just that it can be restored.
 */

// Memento - stores the internal state of the Originator
class TextEditorMemento {
  final String content;
  final String timestamp;
  
  TextEditorMemento(this.content) : timestamp = DateTime.now().toString();
  
  String get getContent => content;
  String get getTimestamp => timestamp;
}

// Originator - creates a memento containing a snapshot of its current state
class TextEditor {
  String _content = '';
  
  void write(String text) {
    _content += text;
    print('Text: "$text" added');
  }
  
  void setContent(String newContent) {
    _content = newContent;
  }
  
  String get content => _content;
  
  TextEditorMemento save() {
    print('Saving current state...');
    return TextEditorMemento(_content);
  }
  
  void restore(TextEditorMemento memento) {
    _content = memento.getContent;
    print('Restored state from ${memento.getTimestamp}');
    print('Current content: "$_content"');
  }
}

// Caretaker - manages mementos, never operates on their contents
class History {
  final List<TextEditorMemento> _mementos = [];
  
  void push(TextEditorMemento memento) {
    _mementos.add(memento);
  }
  
  TextEditorMemento? pop() {
    if (_mementos.isEmpty) {
      return null;
    }
    return _mementos.removeLast();
  }
  
  int get size => _mementos.length;
}

// Example 2: Game State Memento
// Shows how Memento can be used for game saves

class GameStateMemento {
  final int level;
  final int health;
  final int score;
  final String position;
  
  GameStateMemento(this.level, this.health, this.score, this.position);
  
  int get getLevel => level;
  int get getHealth => health;
  int get getScore => score;
  String get getPosition => position;
}

class GameCharacter {
  int _level = 1;
  int _health = 100;
  int _score = 0;
  String _position = 'Start';
  
  void moveTo(String newPosition) {
    _position = newPosition;
    print('Moved to $_position');
  }
  
  void takeDamage(int damage) {
    _health -= damage;
    if (_health < 0) _health = 0;
    print('Took $damage damage. Health: $_health');
  }
  
  void gainScore(int points) {
    _score += points;
    print('Gained $points points. Score: $_score');
  }
  
  void levelUp() {
    _level++;
    _health = 100;
    print('Level up! Now at level $_level');
  }
  
  void displayStatus() {
    print('=== Character Status ===');
    print('Level: $_level');
    print('Health: $_health');
    print('Score: $_score');
    print('Position: $_position');
    print('=====================');
  }
  
  GameStateMemento saveState() {
    print('Saving game state...');
    return GameStateMemento(_level, _health, _score, _position);
  }
  
  void restoreState(GameStateMemento memento) {
    _level = memento.getLevel;
    _health = memento.getHealth;
    _score = memento.getScore;
    _position = memento.getPosition;
    print('Game state restored!');
    displayStatus();
  }
}

class GameSaveManager {
  final List<GameStateMemento> _saves = [];
  
  void createSave(GameStateMemento save) {
    _saves.add(save);
    print('Save created. Total saves: ${_saves.length}');
  }
  
  GameStateMemento? loadSave(int index) {
    if (index >= 0 && index < _saves.length) {
      print('Loading save ${index + 1}...');
      return _saves[index];
    }
    return null;
  }
  
  int get saveCount => _saves.length;
}

// Example 3: Configuration Memento
// Shows how Memento can be used for configuration management

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

// Demo code
void main() {
  print('=== Memento Pattern Demo ===\n');
  
  // Example 1: Text Editor with Undo
  print('--- Text Editor with Undo ---');
  
  final editor = TextEditor();
  final history = History();
  
  editor.write('Hello ');
  history.push(editor.save());
  
  editor.write('World ');
  history.push(editor.save());
  
  editor.write('!');
  history.push(editor.save());
  
  print('\nCurrent content: "${editor.content}"');
  print('History size: ${history.size}');
  
  print('\nPerforming undo...');
  final memento1 = history.pop();
  if (memento1 != null) {
    editor.restore(memento1);
  }
  
  print('\nPerforming undo...');
  final memento2 = history.pop();
  if (memento2 != null) {
    editor.restore(memento2);
  }
  
  print('');
  
  // Example 2: Game Save System
  print('--- Game Save System ---');
  
  final player = GameCharacter();
  final saveManager = GameSaveManager();
  
  print('\nInitial state:');
  player.displayStatus();
  
  print('\nPlaying game...');
  player.moveTo('Forest');
  player.gainScore(100);
  player.takeDamage(10);
  
  print('\nCreating save 1...');
  saveManager.createSave(player.saveState());
  
  print('\nContinuing game...');
  player.moveTo('Castle');
  player.levelUp();
  player.gainScore(500);
  player.takeDamage(30);
  
  print('\nCreating save 2...');
  saveManager.createSave(player.saveState());
  
  print('\nCurrent state:');
  player.displayStatus();
  
  print('\nLoading save 1...');
  final save1 = saveManager.loadSave(0);
  if (save1 != null) {
    player.restoreState(save1);
  }
  
  print('');
  
  // Example 3: Configuration Management
  print('--- Configuration Management Example ---');
  
  final settings = ApplicationSettings();
  
  print('\nDefault settings:');
  settings.displaySettings();
  
  final originalConfig = settings.saveConfiguration();
  
  print('\nChanging settings...');
  settings.setTheme('dark');
  settings.setFontSize(14);
  settings.setNotificationsEnabled(false);
  
  print('\nNew settings:');
  settings.displaySettings();
  
  print('\nRestoring original settings...');
  settings.restoreConfiguration(originalConfig);
}
