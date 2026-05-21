export interface Iterator<T> {
  hasNext(): boolean;
  next(): T;
}

export interface Aggregate<T> {
  createIterator(): Iterator<T>;
}
