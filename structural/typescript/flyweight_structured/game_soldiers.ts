import { SoldierType } from './interfaces';

export class ConcreteSoldierType implements SoldierType {
  constructor(
    private uniform: string,
    private speed: number,
    private rank: string
  ) {}
  
  render(x: number, y: number, weapon: string): void {
    console.log(`Rendering ${this.rank} soldier at (${x}, ${y}) with ${this.uniform} uniform, speed ${this.speed}, holding ${weapon}`);
  }
  
  getUniform(): string {
    return this.uniform;
  }
  
  getSpeed(): number {
    return this.speed;
  }
}

export class SoldierTypeFactory {
  private soldierTypes: Map<string, SoldierType> = new Map();
  
  private getKey(uniform: string, speed: number, rank: string): string {
    return `${uniform}|${speed}|${rank}`;
  }
  
  getSoldierType(uniform: string, speed: number, rank: string): SoldierType {
    const key = this.getKey(uniform, speed, rank);
    
    if (!this.soldierTypes.has(key)) {
      console.log(`Creating new soldier type: ${rank}`);
      this.soldierTypes.set(key, new ConcreteSoldierType(uniform, speed, rank));
    } else {
      console.log(`Reusing existing soldier type: ${rank}`);
    }
    
    return this.soldierTypes.get(key)!;
  }
  
  getTotalSoldierTypes(): number {
    return this.soldierTypes.size;
  }
}

export class Soldier {
  constructor(
    private x: number,
    private y: number,
    private weapon: string,
    private soldierType: SoldierType
  ) {}
  
  render(): void {
    this.soldierType.render(this.x, this.y, this.weapon);
  }
  
  move(newX: number, newY: number): void {
    this.x = newX;
    this.y = newY;
  }
}
