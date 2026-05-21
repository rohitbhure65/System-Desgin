import 'interfaces.dart';

class Manager extends Employee {
  final String _name;
  final double _baseSalary;
  final double _bonus;
  
  Manager(this._name, this._baseSalary, this._bonus);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitManager(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  double get bonus => _bonus;
}

class Developer extends Employee {
  final String _name;
  final double _baseSalary;
  final int _overtimeHours;
  
  Developer(this._name, this._baseSalary, this._overtimeHours);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitDeveloper(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  int get overtimeHours => _overtimeHours;
}

class Designer extends Employee {
  final String _name;
  final double _baseSalary;
  final int _projectsCompleted;
  
  Designer(this._name, this._baseSalary, this._projectsCompleted);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitDesigner(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
  
  int get projectsCompleted => _projectsCompleted;
}

class BaseEmployee extends Employee {
  final String _name;
  final double _baseSalary;
  
  BaseEmployee(this._name, this._baseSalary);
  
  @override
  void accept(SalaryVisitor visitor) {
    visitor.visitEmployee(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  double getBaseSalary() => _baseSalary;
}

class SalaryCalculator implements SalaryVisitor {
  double _totalSalary = 0;
  
  @override
  void visitEmployee(Employee employee) {
    final salary = employee.getBaseSalary();
    _totalSalary += salary;
    print('Employee: ${employee.getName()} - \$$salary');
  }
  
  @override
  void visitManager(Manager manager) {
    final salary = manager.getBaseSalary() + manager.bonus;
    _totalSalary += salary;
    print('Manager: ${manager.getName()} - \$$salary (base: \$${manager.getBaseSalary()} + bonus: \$${manager.bonus})');
  }
  
  @override
  void visitDeveloper(Developer developer) {
    final overtimePay = developer.overtimeHours * 50.0;
    final salary = developer.getBaseSalary() + overtimePay;
    _totalSalary += salary;
    print('Developer: ${developer.getName()} - \$$salary (base: \$${developer.getBaseSalary()} + overtime: \$$overtimePay)');
  }
  
  @override
  void visitDesigner(Designer designer) {
    final projectBonus = designer.projectsCompleted * 500.0;
    final salary = designer.getBaseSalary() + projectBonus;
    _totalSalary += salary;
    print('Designer: ${designer.getName()} - \$$salary (base: \$${designer.getBaseSalary()} + project bonus: \$$projectBonus)');
  }
  
  double get totalSalary => _totalSalary;
}
