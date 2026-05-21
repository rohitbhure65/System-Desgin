import { File, Worker, Circle, Square } from './leaves';
import { Directory, Manager, GraphicGroup } from './composites';

function demoComposite(): void {
  console.log('=== Composite Pattern Demo ===\n');
  
  console.log('--- File System Example ---');
  const file1 = new File('file1.txt', 100);
  const file2 = new File('file2.txt', 200);
  const file3 = new File('file3.txt', 150);
  
  const dir1 = new Directory('Documents');
  const dir2 = new Directory('Pictures');
  const rootDir = new Directory('Root');
  
  dir1.add(file1); dir1.add(file2);
  dir2.add(file3);
  rootDir.add(dir1); rootDir.add(dir2);
  
  console.log('\nFile System Structure:');
  rootDir.display();
  console.log(`\nTotal size of Root directory: \${rootDir.getSize()} bytes\n`);
  
  console.log('--- Organization Structure Example ---');
  const ceo = new Manager('John Smith', 'CEO');
  const cto = new Manager('Alice Johnson', 'CTO');
  const cfo = new Manager('Bob Williams', 'CFO');
  
  const dev1 = new Worker('Developer 1', 'Senior Developer');
  const dev2 = new Worker('Developer 2', 'Junior Developer');
  const accountant = new Worker('Accountant', 'Senior Accountant');
  
  cto.add(dev1); cto.add(dev2); cfo.add(accountant);
  ceo.add(cto); ceo.add(cfo);
  
  console.log('\nOrganization Structure:');
  ceo.print();
  console.log();
  
  console.log('--- Graphic Shapes Example ---');
  const circle1 = new Circle('Red Circle');
  const circle2 = new Circle('Blue Circle');
  const square1 = new Square('Green Square');
  
  const group1 = new GraphicGroup('Shapes Group 1');
  const group2 = new GraphicGroup('Shapes Group 2');
  const mainGroup = new GraphicGroup('Main Group');
  
  group1.add(circle1); group1.add(square1);
  group2.add(circle2);
  mainGroup.add(group1); mainGroup.add(group2);
  
  console.log('\nGraphic Structure:');
  mainGroup.draw();
}

demoComposite();
