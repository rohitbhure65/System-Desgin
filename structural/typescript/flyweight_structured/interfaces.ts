// Flyweight Interface - defines the operations that can be performed on flyweight objects
export interface TreeType {
  draw(x: number, y: number): void;
  getName(): string;
  getColor(): string;
}

export interface CharacterFormat {
  apply(text: string): void;
  getFont(): string;
  getSize(): number;
  getColor(): string;
}

export interface SoldierType {
  render(x: number, y: number, weapon: string): void;
  getUniform(): string;
  getSpeed(): number;
}
