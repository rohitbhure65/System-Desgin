import { Book, Fruit, Electronic, ShoppingCart, PriceCalculator, DescriptionGenerator, TaxCalculator } from './shopping_cart';
import { File, Directory, SizeCalculator, XMLExporter } from './file_system';
import { Manager, Developer, Designer, SalaryCalculator } from './employee_salary';

console.log('=== Visitor Pattern Demo ===\n');

// Example 1: Shopping Cart
console.log('--- Shopping Cart Example ---');

const cart = new ShoppingCart();
cart.addItem(new Book('Design Patterns', 'Erich Gamma', 49.99));
cart.addItem(new Fruit('Apple', 1.99, 0.5));
cart.addItem(new Electronic('Apple', 'iPhone 15', 999.99));

console.log('\nCalculating total price:');
const priceCalc = new PriceCalculator();
cart.acceptVisitor(priceCalc);
console.log(`Total: $${priceCalc.getTotalPrice()}`);

console.log('\nGenerating descriptions:');
const descGen = new DescriptionGenerator();
cart.acceptVisitor(descGen);

console.log('\nCalculating tax:');
const taxCalc = new TaxCalculator();
cart.acceptVisitor(taxCalc);
console.log(`Total tax: $${taxCalc.getTotalTax()}`);

// Example 2: File System
console.log('\n--- File System Example ---');

const root = new Directory('root');
const file1 = new File('document.txt', 1024);
const file2 = new File('image.jpg', 2048);
const subdir = new Directory('subdir');
const file3 = new File('data.csv', 512);

subdir.addChild(file3);
root.addChild(file1);
root.addChild(file2);
root.addChild(subdir);

console.log('\nCalculating sizes:');
const sizeCalc = new SizeCalculator();
root.accept(sizeCalc);
console.log(`Total size: ${sizeCalc.getTotalSize()} bytes`);

console.log('\nExporting to XML:');
console.log('<filesystem>');
const xmlExporter = new XMLExporter();
root.accept(xmlExporter);
console.log('</filesystem>');

// Example 3: Employee Salary
console.log('\n--- Employee Salary Example ---');

const employees = [
  new Manager('Alice', 80000, 20000),
  new Developer('Bob', 70000, 10),
  new Designer('Charlie', 65000, 5)
];

console.log('\nCalculating total salary:');
const salaryCalc = new SalaryCalculator();
for (const emp of employees) {
  emp.accept(salaryCalc);
}
console.log(`Total salary: $${salaryCalc.getTotalSalary()}`);
