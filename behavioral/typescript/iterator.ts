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
interface Iterator<T> {
  hasNext(): boolean;
  next(): T;
}

// Aggregate interface - declares the method for creating an iterator
interface Aggregate<T> {
  createIterator(): Iterator<T>;
}

// Concrete Aggregate - implements the aggregate interface
class BookCollection implements Aggregate<string> {
  private items: string[] = [];
  
  add(item: string): void {
    this.items.push(item);
  }
  
  createIterator(): Iterator<string> {
    return new BookIterator(this);
  }
  
  size(): number {
    return this.items.length;
  }
  
  get(index: number): string {
    return this.items[index];
  }
}

// Concrete Iterator
class BookIterator implements Iterator<string> {
  private collection: BookCollection;
  private position: number = 0;
  
  constructor(collection: BookCollection) {
    this.collection = collection;
  }
  
  hasNext(): boolean {
    return this.position < this.collection.size();
  }
  
  next(): string {
    if (this.hasNext()) {
      return this.collection.get(this.position++);
    }
    return '';
  }
}

// Example 2: Tree Traversal Iterator
// Shows how Iterator can be used for tree structures

class TreeNode<T> {
  data: T;
  left: TreeNode<T> | null = null;
  right: TreeNode<T> | null = null;
  
  constructor(data: T) {
    this.data = data;
  }
}

class BinaryTreeIterator<T> implements Iterator<T> {
  private stack: TreeNode<T>[] = [];
  
  constructor(root: TreeNode<T> | null) {
    this.pushLeft(root);
  }
  
  private pushLeft(node: TreeNode<T> | null): void {
    while (node) {
      this.stack.push(node);
      node = node.left;
    }
  }
  
  hasNext(): boolean {
    return this.stack.length > 0;
  }
  
  next(): T {
    if (!this.hasNext()) return null as T;
    
    const node = this.stack.pop()!;
    
    if (node.right) {
      this.pushLeft(node.right);
    }
    
    return node.data;
  }
}

// Example 3: Custom Container with Iterator
// Shows how to implement iterator for a custom data structure

class CustomList<T> implements Aggregate<T> {
  private head: Node<T> | null = null;
  private count: number = 0;
  
  add(item: T): void {
    const newNode = new Node(item);
    if (!this.head) {
      this.head = newNode;
    } else {
      let current = this.head;
      while (current.next) {
        current = current.next;
      }
      current.next = newNode;
    }
    this.count++;
  }
  
  createIterator(): Iterator<T> {
    return new ListIterator(this.head);
  }
}

class Node<T> {
  data: T;
  next: Node<T> | null = null;
  
  constructor(data: T) {
    this.data = data;
  }
}

class ListIterator<T> implements Iterator<T> {
  private current: Node<T> | null;
  
  constructor(head: Node<T> | null) {
    this.current = head;
  }
  
  hasNext(): boolean {
    return this.current !== null;
  }
  
  next(): T {
    if (!this.hasNext()) return null as T;
    const data = this.current!.data;
    this.current = this.current!.next;
    return data;
  }
}

// Demo code
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

// Build a simple binary tree
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
