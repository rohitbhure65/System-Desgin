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
abstract class TreeType {
  void draw(int x, int y);
  String get name;
  String get color;
}

// Concrete Flyweight - implements the flyweight interface and stores intrinsic state
class ConcreteTreeType extends TreeType {
  @override
  final String name;
  @override
  final String color;
  final String texture;
  
  ConcreteTreeType(this.name, this.color, this.texture);
  
  @override
  void draw(int x, int y) {
    print('Drawing $name tree at ($x, $y) with color $color and texture $texture');
  }
}

// Flyweight Factory - creates and manages flyweight objects
class TreeFactory {
  final Map<String, TreeType> _treeTypes = {};
  
  // Helper function to create a unique key for the map
  String _getKey(String name, String color, String texture) {
    return '$name|$color|$texture';
  }
  
  TreeType getTreeType(String name, String color, String texture) {
    var key = _getKey(name, color, texture);
    
    if (!_treeTypes.containsKey(key)) {
      print('Creating new tree type: $name');
      _treeTypes[key] = ConcreteTreeType(name, color, texture);
    } else {
      print('Reusing existing tree type: $name');
    }
    
    return _treeTypes[key]!;
  }
  
  int getTotalTreeTypes() {
    return _treeTypes.length;
  }
}

// Context - contains extrinsic state and uses flyweight objects
class Tree {
  final int x;
  final int y;
  final TreeType treeType;
  
  Tree(this.x, this.y, this.treeType);
  
  void draw() {
    treeType.draw(x, y);
  }
}

// Example 2: Character Formatting in Text Editor
// Shows how Flyweight can be used for text rendering

abstract class CharacterFormat {
  void apply(String text);
  String get font;
  int get size;
  String get color;
}

class ConcreteCharacterFormat extends CharacterFormat {
  @override
  final String font;
  @override
  final int size;
  @override
  final String color;
  final bool bold;
  final bool italic;
  
  ConcreteCharacterFormat(this.font, this.size, this.color, this.bold, this.italic);
  
  @override
  void apply(String text) {
    var output = 'Rendering \'$text\' with font: $font, size: $size, color: $color';
    if (bold) output += ', bold';
    if (italic) output += ', italic';
    print(output);
  }
}

class CharacterFormatFactory {
  final Map<String, CharacterFormat> _formats = {};
  
  String _getKey(String font, int size, String color, bool bold, bool italic) {
    return '$font|$size|$color|${bold ? 'B' : ''}|${italic ? 'I' : ''}';
  }
  
  CharacterFormat getFormat(String font, int size, String color, bool bold, bool italic) {
    var key = _getKey(font, size, color, bold, italic);
    
    if (!_formats.containsKey(key)) {
      print('Creating new format: $font ${size}pt');
      _formats[key] = ConcreteCharacterFormat(font, size, color, bold, italic);
    } else {
      print('Reusing existing format: $font ${size}pt');
    }
    
    return _formats[key]!;
  }
  
  int getTotalFormats() {
    return _formats.length;
  }
}

class Character {
  final String symbol;
  final CharacterFormat format;
  
  Character(this.symbol, this.format);
  
  void render() {
    format.apply(symbol);
  }
}

// Example 3: Game Units
// Shows how Flyweight can be used for game objects

abstract class SoldierType {
  void render(int x, int y, String weapon);
  String get uniform;
  int get speed;
}

class ConcreteSoldierType extends SoldierType {
  @override
  final String uniform;
  @override
  final int speed;
  final String rank;
  
  ConcreteSoldierType(this.uniform, this.speed, this.rank);
  
  @override
  void render(int x, int y, String weapon) {
    print('Rendering $rank soldier at ($x, $y) with $uniform uniform, speed $speed, holding $weapon');
  }
}

class SoldierTypeFactory {
  final Map<String, SoldierType> _soldierTypes = {};
  
  String _getKey(String uniform, int speed, String rank) {
    return '$uniform|$speed|$rank';
  }
  
  SoldierType getSoldierType(String uniform, int speed, String rank) {
    var key = _getKey(uniform, speed, rank);
    
    if (!_soldierTypes.containsKey(key)) {
      print('Creating new soldier type: $rank');
      _soldierTypes[key] = ConcreteSoldierType(uniform, speed, rank);
    } else {
      print('Reusing existing soldier type: $rank');
    }
    
    return _soldierTypes[key]!;
  }
  
  int getTotalSoldierTypes() {
    return _soldierTypes.length;
  }
}

class Soldier {
  int x, y;
  final String weapon;
  final SoldierType soldierType;
  
  Soldier(this.x, this.y, this.weapon, this.soldierType);
  
  void render() {
    soldierType.render(x, y, weapon);
  }
  
  void move(int newX, int newY) {
    x = newX;
    y = newY;
  }
}

// Demo code
void main() {
  print('=== Flyweight Pattern Demo ===\n');
  
  // Example 1: Forest Trees
  print('--- Forest Trees Example ---');
  
  var treeFactory = TreeFactory();
  
  // Create trees with shared types
  var forest = <Tree>[];
  
  forest.add(Tree(10, 20, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.add(Tree(30, 40, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  forest.add(Tree(50, 60, treeFactory.getTreeType('Oak', 'Green', 'Rough')));
  
  forest.add(Tree(15, 25, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  forest.add(Tree(35, 45, treeFactory.getTreeType('Pine', 'Dark Green', 'Smooth')));
  
  forest.add(Tree(20, 30, treeFactory.getTreeType('Oak', 'Green', 'Rough')));  // Reusing Oak
  
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
  
  army.add(Soldier(40, 40, 'Machine Gun', soldierFactory.getSoldierType('Camouflage', 5, 'Private')));  // Reusing
  
  print('\nRendering army:');
  for (var soldier in army) {
    soldier.render();
  }
  
  print('\nTotal unique soldier types: ${soldierFactory.getTotalSoldierTypes()}');
  print('Total soldiers: ${army.length}');
}
