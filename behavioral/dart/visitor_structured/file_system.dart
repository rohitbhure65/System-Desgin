import 'interfaces.dart';

class File implements FileSystemNode {
  final String _name;
  final int _size;
  
  File(this._name, this._size);
  
  @override
  void accept(FileSystemVisitor visitor) {
    visitor.visitFile(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  int getSize() => _size;
}

class Directory implements FileSystemNode {
  final String _name;
  final List<FileSystemNode> _children = [];
  
  Directory(this._name);
  
  void addChild(FileSystemNode child) {
    _children.add(child);
  }
  
  @override
  void accept(FileSystemVisitor visitor) {
    visitor.visitDirectory(this);
  }
  
  @override
  String getName() => _name;
  
  @override
  int getSize() {
    return _children.fold(0, (total, child) => total + child.getSize());
  }
}

class SizeCalculator implements FileSystemVisitor {
  int _totalSize = 0;
  
  @override
  void visitFile(File file) {
    _totalSize += file.getSize();
    print('File: ${file.getName()} - ${file.getSize()} bytes');
  }
  
  @override
  void visitDirectory(Directory directory) {
    print('Directory: ${directory.getName()} - ${directory.getSize()} bytes');
    _totalSize += directory.getSize();
  }
  
  int get totalSize => _totalSize;
}

class XMLExporter implements FileSystemVisitor {
  @override
  void visitFile(File file) {
    print('  <file name="${file.getName()}" size="${file.getSize()}"/>');
  }
  
  @override
  void visitDirectory(Directory directory) {
    print('  <directory name="${directory.getName()}" size="${directory.getSize()}">');
  }
}
