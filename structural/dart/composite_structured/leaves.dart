import 'components.dart';

class FileComponent extends FileSystemComponent {
  final String name;
  final int size;
  FileComponent(this.name, this.size);
  
  @override
  void display([String indent = '']) { print('\$indent File: \$name (\$size bytes)'); }
  @override
  int getSize() { return size; }
}

class Worker extends Employee {
  final String name;
  final String position;
  Worker(this.name, this.position);
  
  @override
  void print([String indent = '']) { print('\$indent Employee: \$name - \$position'); }
}

class CircleGraphic extends Graphic {
  final String name;
  CircleGraphic(this.name);
  @override
  void draw([String indent = '']) { print('\$indent Drawing Circle: \$name'); }
}

class SquareGraphic extends Graphic {
  final String name;
  SquareGraphic(this.name);
  @override
  void draw([String indent = '']) { print('\$indent Drawing Square: \$name'); }
}
