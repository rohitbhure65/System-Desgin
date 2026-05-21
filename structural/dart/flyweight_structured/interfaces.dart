// Flyweight Interface - defines the operations that can be performed on flyweight objects
abstract class TreeType {
  void draw(int x, int y);
  String get name;
  String get color;
}

abstract class CharacterFormat {
  void apply(String text);
  String get font;
  int get size;
  String get color;
}

abstract class SoldierType {
  void render(int x, int y, String weapon);
  String get uniform;
  int get speed;
}
