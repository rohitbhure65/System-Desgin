import { Iterator, Aggregate } from './interfaces';

export class CustomList<T> implements Aggregate<T> {
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

export class ListIterator<T> implements Iterator<T> {
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
