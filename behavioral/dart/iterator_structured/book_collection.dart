import 'interfaces.dart';

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
