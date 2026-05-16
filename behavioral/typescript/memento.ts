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
  private content: string;
  private timestamp: string;
  
  constructor(content: string) {
    this.content = content;
    this.timestamp = this.getCurrentTime();
  }
  
  getContent(): string {
    return this.content;
  }
  
  getTimestamp(): string {
    return this.timestamp;
  }
  
  private getCurrentTime(): string {
    return new Date().toLocaleString();
  }
}

// Originator - creates a memento containing a snapshot of its current state
class TextEditor {
  private content: string = '';
  
  write(text: string): void {
    this.content += text;
    console.log(`Text: "${text}" added`);
  }
  
  setContent(newContent: string): void {
    this.content = newContent;
  }
  
  getContent(): string {
    return this.content;
  }
  
  save(): TextEditorMemento {
    console.log('Saving current state...');
    return new TextEditorMemento(this.content);
  }
  
  restore(memento: TextEditorMemento): void {
    this.content = memento.getContent();
    console.log(`Restored state from ${memento.getTimestamp()}`);
    console.log(`Current content: "${this.content}"`);
  }
}

// Caretaker - manages mementos, never operates on their contents
class History {
  private mementos: TextEditorMemento[] = [];
  
  push(memento: TextEditorMemento): void {
    this.mementos.push(memento);
  }
  
  pop(): TextEditorMemento | null {
    if (this.mementos.length === 0) {
      return null;
    }
    return this.mementos.pop()!;
  }
  
  size(): number {
    return this.mementos.length;
  }
}

// Example 2: Game State Memento
// Shows how Memento can be used for game saves

class GameStateMemento {
  private level: number;
  private health: number;
  private score: number;
  private position: string;
  
  constructor(level: number, health: number, score: number, position: string) {
    this.level = level;
    this.health = health;
    this.score = score;
    this.position = position;
  }
  
  getLevel(): number { return this.level; }
  getHealth(): number { return this.health; }
  getScore(): number { return this.score; }
  getPosition(): string { return this.position; }
}

class GameCharacter {
  private level: number = 1;
  private health: number = 100;
  private score: number = 0;
  private position: string = 'Start';
  
  moveTo(newPosition: string): void {
    this.position = newPosition;
    console.log(`Moved to ${this.position}`);
  }
  
  takeDamage(damage: number): void {
    this.health -= damage;
    if (this.health < 0) this.health = 0;
    console.log(`Took ${damage} damage. Health: ${this.health}`);
  }
  
  gainScore(points: number): void {
    this.score += points;
    console.log(`Gained ${points} points. Score: ${this.score}`);
  }
  
  levelUp(): void {
    this.level++;
    this.health = 100;
    console.log(`Level up! Now at level ${this.level}`);
  }
  
  displayStatus(): void {
    console.log('=== Character Status ===');
    console.log(`Level: ${this.level}`);
    console.log(`Health: ${this.health}`);
    console.log(`Score: ${this.score}`);
    console.log(`Position: ${this.position}`);
    console.log('=====================');
  }
  
  saveState(): GameStateMemento {
    console.log('Saving game state...');
    return new GameStateMemento(this.level, this.health, this.score, this.position);
  }
  
  restoreState(memento: GameStateMemento): void {
    this.level = memento.getLevel();
    this.health = memento.getHealth();
    this.score = memento.getScore();
    this.position = memento.getPosition();
    console.log('Game state restored!');
    this.displayStatus();
  }
}

class GameSaveManager {
  private saves: GameStateMemento[] = [];
  
  createSave(save: GameStateMemento): void {
    this.saves.push(save);
    console.log(`Save created. Total saves: ${this.saves.length}`);
  }
  
  loadSave(index: number): GameStateMemento | null {
    if (index >= 0 && index < this.saves.length) {
      console.log(`Loading save ${index + 1}...`);
      return this.saves[index];
    }
    return null;
  }
  
  getSaveCount(): number {
    return this.saves.length;
  }
}

// Example 3: Configuration Memento
// Shows how Memento can be used for configuration management

class ConfigurationMemento {
  private theme: string;
  private fontSize: number;
  private notificationsEnabled: boolean;
  
  constructor(theme: string, fontSize: number, notifications: boolean) {
    this.theme = theme;
    this.fontSize = fontSize;
    this.notificationsEnabled = notifications;
  }
  
  getTheme(): string { return this.theme; }
  getFontSize(): number { return this.fontSize; }
  getNotificationsEnabled(): boolean { return this.notificationsEnabled; }
}

class ApplicationSettings {
  private theme: string = 'light';
  private fontSize: number = 12;
  private notificationsEnabled: boolean = true;
  
  setTheme(newTheme: string): void {
    this.theme = newTheme;
    console.log(`Theme changed to ${this.theme}`);
  }
  
  setFontSize(size: number): void {
    this.fontSize = size;
    console.log(`Font size set to ${this.fontSize}`);
  }
  
  setNotificationsEnabled(enabled: boolean): void {
    this.notificationsEnabled = enabled;
    console.log(`Notifications ${enabled ? 'enabled' : 'disabled'}`);
  }
  
  displaySettings(): void {
    console.log('=== Current Settings ===');
    console.log(`Theme: ${this.theme}`);
    console.log(`Font Size: ${this.fontSize}`);
    console.log(`Notifications: ${this.notificationsEnabled ? 'Enabled' : 'Disabled'}`);
    console.log('=====================');
  }
  
  saveConfiguration(): ConfigurationMemento {
    return new ConfigurationMemento(this.theme, this.fontSize, this.notificationsEnabled);
  }
  
  restoreConfiguration(memento: ConfigurationMemento): void {
    this.theme = memento.getTheme();
    this.fontSize = memento.getFontSize();
    this.notificationsEnabled = memento.getNotificationsEnabled();
    console.log('Configuration restored!');
    this.displaySettings();
  }
}

// Demo code
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
