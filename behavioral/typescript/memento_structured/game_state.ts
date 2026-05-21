export class GameStateMemento {
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

export class GameCharacter {
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

export class GameSaveManager {
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
