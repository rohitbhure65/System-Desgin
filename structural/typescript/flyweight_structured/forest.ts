import { TreeType } from './interfaces';

// Concrete Flyweight - implements the flyweight interface and stores intrinsic state
export class ConcreteTreeType implements TreeType {
  constructor(
    private name: string,
    private color: string,
    private texture: string
  ) {}
  
  draw(x: number, y: number): void {
    console.log(`Drawing ${this.name} tree at (${x}, ${y}) with color ${this.color} and texture ${this.texture}`);
  }
  
  getName(): string {
    return this.name;
  }
  
  getColor(): string {
    return this.color;
  }
}

// Flyweight Factory - creates and manages flyweight objects
export class TreeFactory {
  private treeTypes: Map<string, TreeType> = new Map();
  
  private getKey(name: string, color: string, texture: string): string {
    return `${name}|${color}|${texture}`;
  }
  
  getTreeType(name: string, color: string, texture: string): TreeType {
    const key = this.getKey(name, color, texture);
    
    if (!this.treeTypes.has(key)) {
      console.log(`Creating new tree type: ${name}`);
      this.treeTypes.set(key, new ConcreteTreeType(name, color, texture));
    } else {
      console.log(`Reusing existing tree type: ${name}`);
    }
    
    return this.treeTypes.get(key)!;
  }
  
  getTotalTreeTypes(): number {
    return this.treeTypes.size;
  }
}

// Context - contains extrinsic state and uses flyweight objects
export class Tree {
  constructor(
    private x: number,
    private y: number,
    private treeType: TreeType
  ) {}
  
  draw(): void {
    this.treeType.draw(this.x, this.y);
  }
}
