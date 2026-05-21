import 'interfaces.dart';

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
