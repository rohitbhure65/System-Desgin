import 'interfaces.dart';

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
