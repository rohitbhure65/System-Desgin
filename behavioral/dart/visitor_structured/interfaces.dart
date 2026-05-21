abstract class Visitor {
  void visitBook(Book book);
  void visitFruit(Fruit fruit);
  void visitElectronic(Electronic electronic);
}

abstract class Item {
  void accept(Visitor visitor);
  double getPrice();
}

abstract class FileSystemVisitor {
  void visitFile(File file);
  void visitDirectory(Directory directory);
}

abstract class FileSystemNode {
  void accept(FileSystemVisitor visitor);
  String getName();
  int getSize();
}

abstract class SalaryVisitor {
  void visitEmployee(Employee employee);
  void visitManager(Manager manager);
  void visitDeveloper(Developer developer);
  void visitDesigner(Designer designer);
}

abstract class Employee {
  void accept(SalaryVisitor visitor);
  String getName();
  double getBaseSalary();
}
