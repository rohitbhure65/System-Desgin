import 'interfaces.dart';
import 'shopping_cart.dart';
import 'file_system.dart';
import 'employee_salary.dart';

void main() {
  print('=== Visitor Pattern Demo ===\n');
  
  // Example 1: Shopping Cart
  print('--- Shopping Cart Example ---');
  
  final cart = ShoppingCart();
  cart.addItem(Book('Design Patterns', 'Erich Gamma', 49.99));
  cart.addItem(Fruit('Apple', 1.99, 0.5));
  cart.addItem(Electronic('Apple', 'iPhone 15', 999.99));
  
  print('\nCalculating total price:');
  final priceCalc = PriceCalculator();
  cart.acceptVisitor(priceCalc);
  print('Total: \$${priceCalc.totalPrice}');
  
  print('\nGenerating descriptions:');
  final descGen = DescriptionGenerator();
  cart.acceptVisitor(descGen);
  
  print('\nCalculating tax:');
  final taxCalc = TaxCalculator();
  cart.acceptVisitor(taxCalc);
  print('Total tax: \$${taxCalc.totalTax}');
  
  // Example 2: File System
  print('\n--- File System Example ---');
  
  final root = Directory('root');
  final file1 = File('document.txt', 1024);
  final file2 = File('image.jpg', 2048);
  final subdir = Directory('subdir');
  final file3 = File('data.csv', 512);
  
  subdir.addChild(file3);
  root.addChild(file1);
  root.addChild(file2);
  root.addChild(subdir);
  
  print('\nCalculating sizes:');
  final sizeCalc = SizeCalculator();
  root.accept(sizeCalc);
  print('Total size: ${sizeCalc.totalSize} bytes');
  
  print('\nExporting to XML:');
  print('<filesystem>');
  final xmlExporter = XMLExporter();
  root.accept(xmlExporter);
  print('</filesystem>');
  
  // Example 3: Employee Salary
  print('\n--- Employee Salary Example ---');
  
  final employees = <Employee>[
    Manager('Alice', 80000, 20000),
    Developer('Bob', 70000, 10),
    Designer('Charlie', 65000, 5)
  ];
  
  print('\nCalculating total salary:');
  final salaryCalc = SalaryCalculator();
  for (final emp in employees) {
    emp.accept(salaryCalc);
  }
  print('Total salary: \$${salaryCalc.totalSalary}');
}
