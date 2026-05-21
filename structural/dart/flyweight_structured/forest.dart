import 'interfaces.dart';

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
