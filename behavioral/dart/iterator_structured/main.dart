import 'interfaces.dart';
import 'book_collection.dart';
import 'tree_iterator.dart';
import 'custom_list.dart';

void main() {
  print('=== Iterator Pattern Demo ===\n');
  
  // Example 1: Book Collection
  print('--- Book Collection Example ---');
  
  final books = BookCollection();
  books.add('Design Patterns');
  books.add('Clean Code');
  books.add('Refactoring');
  books.add('The Pragmatic Programmer');
  
  final bookIterator = books.createIterator();
  
  print('\nIterating through books:');
  while (bookIterator.hasNext()) {
    print('  - ${bookIterator.next()}');
  }
  
  print('');
  
  // Example 2: Binary Tree Traversal
  print('--- Binary Tree Traversal Example ---');
  
  final root = TreeNode(5);
  root.left = TreeNode(3);
  root.right = TreeNode(7);
  root.left!.left = TreeNode(1);
  root.left!.right = TreeNode(4);
  root.right!.left = TreeNode(6);
  root.right!.right = TreeNode(9);
  
  final treeIterator = BinaryTreeIterator(root);
  
  print('\nIn-order traversal:');
  while (treeIterator.hasNext()) {
    print('  ${treeIterator.next()}');
  }
  
  print('');
  
  // Example 3: Custom List Iterator
  print('--- Custom List Iterator Example ---');
  
  final numbers = CustomList<int>();
  numbers.add(10);
  numbers.add(20);
  numbers.add(30);
  numbers.add(40);
  numbers.add(50);
  
  final listIterator = numbers.createIterator();
  
  print('\nIterating through custom list:');
  while (listIterator.hasNext()) {
    print('  ${listIterator.next()}');
  }
}
