import { Iterator, Aggregate } from './interfaces';

export class BookCollection implements Aggregate<string> {
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

export class BookIterator implements Iterator<string> {
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
