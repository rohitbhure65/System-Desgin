import { TextEditor, History } from './text_editor';
import { GameCharacter, GameSaveManager } from './game_state';
import { ApplicationSettings } from './configuration';

console.log('=== Memento Pattern Demo ===\n');

// Example 1: Text Editor with Undo
console.log('--- Text Editor with Undo ---');

const editor = new TextEditor();
const history = new History();

editor.write('Hello ');
history.push(editor.save());

editor.write('World ');
history.push(editor.save());

editor.write('!');
history.push(editor.save());

console.log(`\nCurrent content: "${editor.getContent()}"`);
console.log(`History size: ${history.size()}`);

console.log('\nPerforming undo...');
const memento1 = history.pop();
if (memento1) {
  editor.restore(memento1);
}

console.log('\nPerforming undo...');
const memento2 = history.pop();
if (memento2) {
  editor.restore(memento2);
}

console.log('');

// Example 2: Game Save System
console.log('--- Game Save System ---');

const player = new GameCharacter();
const saveManager = new GameSaveManager();

console.log('\nInitial state:');
player.displayStatus();

console.log('\nPlaying game...');
player.moveTo('Forest');
player.gainScore(100);
player.takeDamage(10);

console.log('\nCreating save 1...');
saveManager.createSave(player.saveState());

console.log('\nContinuing game...');
player.moveTo('Castle');
player.levelUp();
player.gainScore(500);
player.takeDamage(30);

console.log('\nCreating save 2...');
saveManager.createSave(player.saveState());

console.log('\nCurrent state:');
player.displayStatus();

console.log('\nLoading save 1...');
const save1 = saveManager.loadSave(0);
if (save1) {
  player.restoreState(save1);
}

console.log('');

// Example 3: Configuration Management
console.log('--- Configuration Management Example ---');

const settings = new ApplicationSettings();

console.log('\nDefault settings:');
settings.displaySettings();

const originalConfig = settings.saveConfiguration();

console.log('\nChanging settings...');
settings.setTheme('dark');
settings.setFontSize(14);
settings.setNotificationsEnabled(false);

console.log('\nNew settings:');
settings.displaySettings();

console.log('\nRestoring original settings...');
settings.restoreConfiguration(originalConfig);
