import 'text_editor.dart';
import 'game_state.dart';
import 'configuration.dart';

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
