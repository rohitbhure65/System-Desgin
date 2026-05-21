abstract class Iterator<T> {
  bool hasNext();
  T next();
}

abstract class Aggregate<T> {
  Iterator<T> createIterator();
}
