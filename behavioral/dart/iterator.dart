/*
 * ITERATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Iterator pattern provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
 * It traverses the elements of a collection without knowing its internal structure.
 * 
 * WHY DOES IT EXIST?
 * - When you want to access a collection's contents without exposing its internal representation
 * - When you want to provide multiple ways to traverse a collection
 * - When you want to provide a uniform interface for traversing different data structures
 * 
 * WHEN TO USE IT?
 * - When you have a collection of objects and want to traverse it without exposing its internal structure
 * - When you want to provide multiple traversal algorithms for the same collection
 * - When you want to simplify the interface for accessing a complex data structure
 * - Common use cases: collections, tree structures, database result sets, file systems
 * 
 * PROS:
 * - Single Responsibility Principle (separates traversal logic from the collection)
 * - Open/Closed Principle (can add new iterators without changing the collection)
 * - Provides a uniform interface for traversing different collections
 * - Can support multiple traversals simultaneously
 * 
 * CONS:
 * - Can be overkill for simple collections
 * - May violate encapsulation if the iterator exposes too much about the collection
 * - Can be less efficient than direct access
 * - May complicate the code for simple use cases
 * 
 * REAL-WORLD ANALOGY:
 * Think of a TV remote control with channel up/down buttons. You don't need to know how the TV stores channels - you just use the next/previous buttons to navigate. The remote (iterator) provides a simple interface to traverse the channels (collection) without knowing the internal channel storage mechanism.
 */

// Iterator interface - declares the operations for traversing
abstract class Iterator<T> {
  bool hasNext();
  T next();
}

// Aggregate interface - declares the method for creating an iterator
abstract class Aggregate<T> {
  Iterator<T> createIterator();
}

// Concrete Aggregate - implements the aggregate interface
class BookCollection implements Aggregate<String> {
  final List<String> _items = [];
  
  void add(String item) {
    _items.add(item);
  }
  
  @override
  Iterator<String> createIterator() {
    return BookIterator(this);
  }
  
  int size() => _items.length;
  
  String get(int index) => _items[index];
}

// Concrete Iterator
class BookIterator implements Iterator<String> {
  final BookCollection _collection;
  int _position = 0;
  
  BookIterator(this._collection);
  
  @override
  bool hasNext() {
    return _position < _collection.size();
  }
  
  @override
  String next() {
    if (hasNext()) {
      return _collection.get(_position++);
    }
    return '';
  }
}

// Example 2: Tree Traversal Iterator
// Shows how Iterator can be used for tree structures

class TreeNode<T> {
  T data;
  TreeNode<T>? left;
  TreeNode<T>? right;
  
  TreeNode(this.data);
}

class BinaryTreeIterator<T> implements Iterator<T> {
  final List<TreeNode<T>> _stack = [];
  
  BinaryTreeIterator(TreeNode<T>? root) {
    _pushLeft(root);
  }
  
  void _pushLeft(TreeNode<T>? node) {
    while (node != null) {
      _stack.add(node);
      node = node.left;
    }
  }
  
  @override
  bool hasNext() {
    return _stack.isNotEmpty;
  }
  
  @override
  T next() {
    if (!hasNext()) return null as T;
    
    final node = _stack.removeLast();
    
    if (node.right != null) {
      _pushLeft(node.right);
    }
    
    return node.data;
  }
}

// Example 3: Custom Container with Iterator
// Shows how to implement iterator for a custom data structure

class CustomList<T> implements Aggregate<T> {
  _Node<T>? _head;
  
  void add(T item) {
    final newNode = _Node(item);
    if (_head == null) {
      _head = newNode;
    } else {
      _Node<T>? current = _head;
      while (current!.next != null) {
        current = current.next;
      }
      current.next = newNode;
    }
  }
  
  @override
  Iterator<T> createIterator() {
    return ListIterator(_head);
  }
}

class _Node<T> {
  T data;
  _Node<T>? next;
  
  _Node(this.data);
}

class ListIterator<T> implements Iterator<T> {
  _Node<T>? _current;
  
  ListIterator(this._current);
  
  @override
  bool hasNext() {
    return _current != null;
  }
  
  @override
  T next() {
    if (!hasNext()) return null as T;
    final data = _current!.data;
    _current = _current!.next;
    return data;
  }
}

// Demo code
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
  
  // Build a simple binary tree
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
