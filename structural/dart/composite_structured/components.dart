abstract class FileSystemComponent {
  void display([String indent = '']);
  int getSize();
  
  void add(FileSystemComponent component) { print('Cannot add to a file'); }
  void remove(FileSystemComponent component) { print('Cannot remove from a file'); }
  FileSystemComponent? getChild(int index) { return null; }
}

abstract class Employee {
  void print([String indent = '']);
  void add(Employee employee) { print('Cannot add to a regular employee'); }
  void remove(Employee employee) { print('Cannot remove from a regular employee'); }
}

abstract class Graphic {
  void draw([String indent = '']);
}
