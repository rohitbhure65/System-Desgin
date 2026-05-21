import { BookCollection } from './book_collection';
import { TreeNode, BinaryTreeIterator } from './tree_iterator';
import { CustomList } from './custom_list';

console.log('=== Iterator Pattern Demo ===\n');

// Example 1: Book Collection
console.log('--- Book Collection Example ---');

const books = new BookCollection();
books.add('Design Patterns');
books.add('Clean Code');
books.add('Refactoring');
books.add('The Pragmatic Programmer');

const bookIterator = books.createIterator();

console.log('\nIterating through books:');
while (bookIterator.hasNext()) {
  console.log('  - ' + bookIterator.next());
}

console.log('');

// Example 2: Binary Tree Traversal
console.log('--- Binary Tree Traversal Example ---');

const root = new TreeNode(5);
root.left = new TreeNode(3);
root.right = new TreeNode(7);
root.left.left = new TreeNode(1);
root.left.right = new TreeNode(4);
root.right.left = new TreeNode(6);
root.right.right = new TreeNode(9);

const treeIterator = new BinaryTreeIterator(root);

console.log('\nIn-order traversal:');
while (treeIterator.hasNext()) {
  console.log('  ' + treeIterator.next());
}

console.log('');

// Example 3: Custom List Iterator
console.log('--- Custom List Iterator Example ---');

const numbers = new CustomList<number>();
numbers.add(10);
numbers.add(20);
numbers.add(30);
numbers.add(40);
numbers.add(50);

const listIterator = numbers.createIterator();

console.log('\nIterating through custom list:');
while (listIterator.hasNext()) {
  console.log('  ' + listIterator.next());
}
