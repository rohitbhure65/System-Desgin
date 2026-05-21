import 'forest.dart';
import 'text_editor.dart';
import 'game_soldiers.dart';

void main() {
  print('=== Flyweight Pattern Demo ===\n');
  
  // Example 1: Forest Trees
  print('--- Forest Trees Example ---');
  
  var treeFactory = TreeFactory();
  
  var forest = <Tree>[];
  
  forest.add(Tree(10, 20, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.add(Tree(30, 40, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.add(Tree(50, 60, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
  forest.add(Tree(15, 25, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  forest.add(Tree(35, 45, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  
  forest.add(Tree(20, 30, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
  print('\nDrawing forest:');
  for (var tree in forest) {
    tree.draw();
  }
  
  print('\nTotal unique tree types: ${treeFactory.getTotalTreeTypes()}');
  print('Total trees in forest: ${forest.length}');
  
  print('');
  
  // Example 2: Text Editor Characters
  print('--- Text Editor Characters Example ---');
  
  var formatFactory = CharacterFormatFactory();
  
  var document = <Character>[];
  
  document.add(Character('H', formatFactory.getFormat('Arial', 12, 'Black', true, false)));
  document.add(Character('e', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.add(Character('l', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.add(Character('l', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  document.add(Character('o', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  
  document.add(Character(' ', formatFactory.getFormat('Arial', 12, 'Black', false, false)));
  
  document.add(Character('W', formatFactory.getFormat('Times New Roman', 14, 'Blue', true, true)));
  document.add(Character('o', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.add(Character('r', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.add(Character('l', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  document.add(Character('d', formatFactory.getFormat('Times New Roman', 14, 'Blue', false, true)));
  
  print('\nRendering document:');
  for (var character in document) {
    character.render();
  }
  
  print('\nTotal unique formats: ${formatFactory.getTotalFormats()}');
  print('Total characters: ${document.length}');
  
  print('');
  
  // Example 3: Game Soldiers
  print('--- Game Soldiers Example ---');
  
  var soldierFactory = SoldierTypeFactory();
  
  var army = <Soldier>[];
  
  army.add(Soldier(10, 10, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  army.add(Soldier(20, 20, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  army.add(Soldier(30, 30, 'Rifle', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  
  army.add(Soldier(15, 15, 'Sniper', soldierFactory.getSoldierType('Desert', 4, 'Sergeant')));
  army.add(Soldier(25, 25, 'Sniper', soldierFactory.getSoldierType('Desert', 4, 'Sergeant')));
  
  army.add(Soldier(40, 40, 'Machine Gun', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));
  
  print('\nRendering army:');
  for (var soldier in army) {
    soldier.render();
  }
  
  print('\nTotal unique soldier types: ${soldierFactory.getTotalSoldierTypes()}');
  print('Total soldiers: ${army.length}');
}
