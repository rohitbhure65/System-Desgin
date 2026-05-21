import 'components.dart';

class Directory extends FileSystemComponent {
  final String name;
  final List<FileSystemComponent> _children = [];
  Directory(this.name);
  
  @override
  void add(FileSystemComponent component) { _children.add(component); }
  @override
  void remove(FileSystemComponent component) { _children.remove(component); }
  @override
  FileSystemComponent? getChild(int index) {
    if (index >= 0 && index < _children.length) { return _children[index]; }
    return null;
  }
  
  @override
  void display([String indent = '']) {
    print('\$indent Directory: \$name (\${getSize()} bytes)');
    for (var child in _children) { child.display(indent + '  '); }
  }
  
  @override
  int getSize() {
    int totalSize = 0;
    for (var child in _children) { totalSize += child.getSize(); }
    return totalSize;
  }
}

class Manager extends Employee {
  final String name;
  final String title;
  final List<Employee> _subordinates = [];
  Manager(this.name, this.title);
  
  @override
  void add(Employee employee) { _subordinates.add(employee); }
  @override
  void remove(Employee employee) { _subordinates.remove(employee); }
  
  @override
  void print([String indent = '']) {
    print('\$indent Manager: \$name - \$title');
    for (var subordinate in _subordinates) { subordinate.print(indent + '  '); }
  }
}

class GraphicGroup extends Graphic {
  final String name;
  final List<Graphic> _graphics = [];
  GraphicGroup(this.name);
  
  void add(Graphic graphic) { _graphics.add(graphic); }
  void remove(Graphic graphic) { _graphics.remove(graphic); }
  
  @override
  void draw([String indent = '']) {
    print('\$indent Group: \$name');
    for (var graphic in _graphics) { graphic.draw(indent + '  '); }
  }
}
