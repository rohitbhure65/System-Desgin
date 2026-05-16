/*
 * FLYWEIGHT DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Flyweight pattern lets you fit more objects into the available RAM by sharing common parts of state between multiple objects.
 * It separates intrinsic state (shared) from extrinsic state (unique).
 * 
 * WHY DOES IT EXIST?
 * - When you need to reduce memory usage by sharing objects
 * - When a large number of similar objects should be shared
 * - When most of an object's state can be made extrinsic
 * 
 * WHEN TO USE IT?
 * - When your application uses a large number of objects
 * - When storage costs are high because of the quantity of objects
 * - When most of the object's state can be made extrinsic
 * - When many groups of objects can be replaced by relatively few shared objects
 * - Common use cases: text editors (character formatting), game objects (trees, soldiers), GUI elements (icons, fonts)
 * 
 * PROS:
 * - Reduces memory consumption by sharing objects
 * - Improves performance when many similar objects are needed
 * - Centralized state management
 * - Can be combined with other patterns (Composite, Strategy)
 * 
 * CONS:
 * - May increase runtime complexity due to sharing
 * - Requires careful identification of intrinsic vs extrinsic state
 * - Can make code more complex
 * - May sacrifice some encapsulation (extrinsic state passed to flyweight)
 * 
 * REAL-WORLD ANALOGY:
 * Think of a coffee shop. They don't make a new cup for every customer - they reuse cups (intrinsic state: the cup itself). What changes is the coffee inside (extrinsic state: the type of coffee). The cup is shared (flyweight), while the coffee content varies per customer.
 */

// Flyweight Interface - defines the operations that can be performed on flyweight objects
interface TreeType {
  draw(x: number, y: number): void;
  getName(): string;
  getColor(): string;
}

// Concrete Flyweight - implements the flyweight interface and stores intrinsic state
class ConcreteTreeType implements TreeType {
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
class TreeFactory {
  private treeTypes: Map<string, TreeType> = new Map();
  
  // Helper function to create a unique key for the map
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
class Tree {
  constructor(
    private x: number,
    private y: number,
    private treeType: TreeType
  ) {}
  
  draw(): void {
    this.treeType.draw(this.x, this.y);
  }
}

// Example 2: Character Formatting in Text Editor
// Shows how Flyweight can be used for text rendering

interface CharacterFormat {
  apply(text: string): void;
  getFont(): string;
  getSize(): number;
  getColor(): string;
}

class ConcreteCharacterFormat implements CharacterFormat {
  constructor(
    private font: string,
    private size: number,
    private color: string,
    private bold: boolean,
    private italic: boolean
  ) {}
  
  apply(text: string): void {
    let output = `Rendering '${text}' with font: ${this.font}, size: ${this.size}, color: ${this.color}`;
    if (this.bold) output += ', bold';
    if (this.italic) output += ', italic';
    console.log(output);
  }
  
  getFont(): string {
    return this.font;
  }
  
  getSize(): number {
    return this.size;
  }
  
  getColor(): string {
    return this.color;
  }
}

class CharacterFormatFactory {
  private formats: Map<string, CharacterFormat> = new Map();
  
  private getKey(font: string, size: number, color: string, bold: boolean, italic: boolean): string {
    return `${font}|${size}|${color}|${bold ? 'B' : ''}|${italic ? 'I' : ''}`;
  }
  
  getFormat(font: string, size: number, color: string, bold: boolean, italic: boolean): CharacterFormat {
    const key = this.getKey(font, size, color, bold, italic);
    
    if (!this.formats.has(key)) {
      console.log(`Creating new format: ${font} ${size}pt`);
      this.formats.set(key, new ConcreteCharacterFormat(font, size, color, bold, italic));
    } else {
      console.log(`Reusing existing format: ${font} ${size}pt`);
    }
    
    return this.formats.get(key)!;
  }
  
  getTotalFormats(): number {
    return this.formats.size;
  }
}

class Character {
  constructor(
    private symbol: string,
    private format: CharacterFormat
  ) {}
  
  render(): void {
    this.format.apply(this.symbol);
  }
}

// Example 3: Game Units
// Shows how Flyweight can be used for game objects

interface SoldierType {
  render(x: number, y: number, weapon: string): void;
  getUniform(): string;
  getSpeed(): number;
}

class ConcreteSoldierType implements SoldierType {
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

class SoldierTypeFactory {
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

class Soldier {
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

// Demo code
function demoFlyweight(): void {
  console.log('=== Flyweight Pattern Demo ===\n');
  
  // Example 1: Forest Trees
  console.log('--- Forest Trees Example ---');
  
  const treeFactory = new TreeFactory();
  
  // Create trees with shared types
  const forest: Tree[] = [];
  
  forest.push(new Tree(10, 20, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.push(new Tree(30, 40, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.push(new Tree(50, 60, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
  forest.push(new Tree(15, 25, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  forest.push(new Tree(35, 45, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  
  forest.push(new Tree(20, 30, treeFactory.getTreeType('Oak', 'Green', 'Rough')));  // Reusing Oak
  
  console.log('\nDrawing forest:');
  for (const tree of forest) {
    tree.draw();
  }
  
  console.log(`\nTotal unique tree types: ${treeFactory.getTotalTreeTypes()}`);
  console.log(`Total trees in forest: ${forest.length}`);
  
  console.log();
  
  // Example 2: Text Editor Characters
  console.log('--- Text Editor Characters Example ---');
  
  const formatFactory = new CharacterFormatFactory();
  
  const document: Character[] = [];
  
  document.push(new Character('H', formatFactory.getFormat('Arial', 12, 'Black', true, false)));
  document.push(new Character('e', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.push(new Character('l', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.push(new Character('l', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.push(new Character('o', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  
  document.push(new Character(' ', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  
  document.push(new Character('W', formatFactory.getFormat('Times New Roman', 14, 'Blue', true, true)));
  document.push(new Character('o', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.push(new Character('r', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.push(new Character('l', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.push(new Character('d', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  
  console.log('\nRendering document:');
  for (const character of document) {
    character.render();
  }
  
  console.log(`\nTotal unique formats: ${formatFactory.getTotalFormats()}`);
  console.log(`Total characters: ${document.length}`);
  
  console.log();
  
  // Example 3: Game Soldiers
  console.log('--- Game Soldiers Example ---');
  
  const soldierFactory = new SoldierTypeFactory();
  
  const army: Soldier[] = [];
  
  army.push(new Soldier(10, 10, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  army.push(new Soldier(20, 20, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  army.push(new Soldier(30, 30, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  
  army.push(new Soldier(15, 15, 'Sniper', soldierFactory.getSoldierType('Desert', 4, 'Sergeant')));
  army.push(new Soldier(25, 25, 'Sniper', soldierFactory.getSoldierType('Desert', 4, 'Sergeant')));
  
  army.push(new Soldier(40, 40, 'Machine Gun', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));  // Reusing
  
  console.log('\nRendering army:');
  for (const soldier of army) {
    soldier.render();
  }
  
  console.log(`\nTotal unique soldier types: ${soldierFactory.getTotalSoldierTypes()}`);
  console.log(`Total soldiers: ${army.length}`);
}

// Run the demo
demoFlyweight();
