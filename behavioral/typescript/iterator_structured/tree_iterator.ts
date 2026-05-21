import { Iterator } from './interfaces';

export class TreeNode<T> {
  data: T;
  left: TreeNode<T> | null = null;
  right: TreeNode<T> | null = null;
  
  constructor(data: T) {
    this.data = data;
  }
}

export class BinaryTreeIterator<T> implements Iterator<T> {
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
