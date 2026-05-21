import 'interfaces.dart';

class Rectangle extends Prototype {
  int _width;
  int _height;
  String _color;
  
  Rectangle(this._width, this._height, this._color);
  
  @override
  Rectangle clone() {
    return Rectangle(_width, _height, _color);
  }
  
  @override
  void display() {
    print('Rectangle: ${_width}x${_height}, Color: $_color');
  }
  
  @override
  String get type => 'Rectangle';
  
  void setWidth(int width) => _width = width;
  void setHeight(int height) => _height = height;
  void setColor(String color) => _color = color;
}

class Circle extends Prototype {
  int _radius;
  String _color;
  
  Circle(this._radius, this._color);
  
  @override
  Circle clone() {
    return Circle(_radius, _color);
  }
  
  @override
  void display() {
    print('Circle: Radius $_radius, Color: $_color');
  }
  
  @override
  String get type => 'Circle';
  
  void setRadius(int radius) => _radius = radius;
  void setColor(String color) => _color = color;
}

class Employee extends Prototype {
  String _name;
  String _department;
  int _salary;
  List<String> _skills;
  
  Employee(this._name, this._department, this._salary, [List<String>? skills])
      : _skills = skills ?? [];
  
  @override
  Employee clone() {
    var skillsCopy = List<String>.from(_skills);
    return Employee(_name, _department, _salary, skillsCopy);
  }
  
  @override
  void display() {
    print('Employee: $_name, Dept: $_department, Salary: \$$_salary');
    print('Skills: ${_skills.join(", ")}');
  }
  
  @override
  String get type => 'Employee';
  
  void addSkill(String skill) => _skills.add(skill);
  void setName(String name) => _name = name;
  void setSalary(int salary) => _salary = salary;
}

class Document extends Prototype {
  String _title;
  String _content;
  
  Document(this._title, this._content);
  
  @override
  Document clone() {
    return Document(_title, _content);
  }
  
  @override
  void display() {
    print('Document: $_title');
    print('Content: $_content');
  }
  
  @override
  String get type => 'Document';
  
  void appendContent(String text) => _content += text;
  void setTitle(String title) => _title = title;
}

class GameCharacter extends Prototype {
  String _name;
  int _health;
  int _attack;
  int _defense;
  List<String> _inventory;
  
  GameCharacter(this._name, this._health, this._attack, this._defense,
      [List<String>? inventory])
      : _inventory = inventory ?? [];
  
  @override
  GameCharacter clone() {
    return GameCharacter(
        _name, _health, _attack, _defense, List<String>.from(_inventory));
  }
  
  @override
  void display() {
    print('Character: $_name');
    print('  Health: $_health, Attack: $_attack, Defense: $_defense');
    print('  Inventory: ${_inventory.join(", ")}');
  }
  
  @override
  String get type => 'GameCharacter';
  
  void addItem(String item) => _inventory.add(item);
  void setName(String name) => _name = name;
  void takeDamage(int amount) => _health = (_health - amount).clamp(0, double.infinity).toInt();
}
