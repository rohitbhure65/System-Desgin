import { Tree, TreeFactory } from './forest';
import { Character, CharacterFormatFactory } from './text_editor';
import { Soldier, SoldierTypeFactory } from './game_soldiers';

function demoFlyweight(): void {
  console.log('=== Flyweight Pattern Demo ===\n');
  
  // Example 1: Forest Trees
  console.log('--- Forest Trees Example ---');
  
  const treeFactory = new TreeFactory();
  
  const forest: Tree[] = [];
  
  forest.push(new Tree(10, 20, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.push(new Tree(30, 40, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.push(new Tree(50, 60, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
  forest.push(new Tree(15, 25, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  forest.push(new Tree(35, 45, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  
  forest.push(new Tree(20, 30, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
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
  
  army.push(new Soldier(40, 40, 'Machine Gun', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  
  console.log('\nRendering army:');
  for (const soldier of army) {
    soldier.render();
  }
  
  console.log(`\nTotal unique soldier types: ${soldierFactory.getTotalSoldierTypes()}`);
  console.log(`Total soldiers: ${army.length}`);
}

// Run the demo
demoFlyweight();
