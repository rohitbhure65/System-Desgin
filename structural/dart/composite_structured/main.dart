import 'leaves.dart';
import 'composites.dart';

void main() {
  print('=== Composite Pattern Demo ===\n');
  
  print('--- File System Example ---');
  var file1 = FileComponent('file1.txt', 100);
  var file2 = FileComponent('file2.txt', 200);
  var file3 = FileComponent('file3.txt', 150);
  
  var dir1 = Directory('Documents');
  var dir2 = Directory('Pictures');
  var rootDir = Directory('Root');
  
  dir1.add(file1);
  dir1.add(file2);
  dir2.add(file3);
  rootDir.add(dir1);
  rootDir.add(dir2);
  
  print('\nFile System Structure:');
  rootDir.display();
  print('\nTotal size of Root directory: \${rootDir.getSize()} bytes');
  print('');
  
  print('--- Organization Structure Example ---');
  var ceo = Manager('John Smith', 'CEO');
  var cto = Manager('Alice Johnson', 'CTO');
  var cfo = Manager('Bob Williams', 'CFO');
  var dev1 = Worker('Developer 1', 'Senior Developer');
  var dev2 = Worker('Developer 2', 'Junior Developer');
  var accountant = Worker('Accountant', 'Senior Accountant');
  
  cto.add(dev1);
  cto.add(dev2);
  cfo.add(accountant);
  ceo.add(cto);
  ceo.add(cfo);
  
  print('\nOrganization Structure:');
  ceo.print();
  print('');
  
  print('--- Graphic Shapes Example ---');
  var circle1 = CircleGraphic('Red Circle');
  var circle2 = CircleGraphic('Blue Circle');
  var square1 = SquareGraphic('Green Square');
  
  var group1 = GraphicGroup('Shapes Group 1');
  var group2 = GraphicGroup('Shapes Group 2');
  var mainGroup = GraphicGroup('Main Group');
  
  group1.add(circle1);
  group1.add(square1);
  group2.add(circle2);
  mainGroup.add(group1);
  mainGroup.add(group2);
  
  print('\nGraphic Structure:');
  mainGroup.draw();
}
