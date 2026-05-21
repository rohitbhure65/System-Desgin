class TextEditorMemento {
  final String content;
  final String timestamp;
  
  TextEditorMemento(this.content) : timestamp = DateTime.now().toString();
  
  String get getContent => content;
  String get getTimestamp => timestamp;
}

class TextEditor {
  String _content = '';
  
  void write(String text) {
    _content += text;
    print('Text: "$text" added');
  }
  
  void setContent(String newContent) {
    _content = newContent;
  }
  
  String get content => _content;
  
  TextEditorMemento save() {
    print('Saving current state...');
    return TextEditorMemento(_content);
  }
  
  void restore(TextEditorMemento memento) {
    _content = memento.getContent;
    print('Restored state from ${memento.getTimestamp}');
    print('Current content: "$_content"');
  }
}

class History {
  final List<TextEditorMemento> _mementos = [];
  
  void push(TextEditorMemento memento) {
    _mementos.add(memento);
  }
  
  TextEditorMemento? pop() {
    if (_mementos.isEmpty) {
      return null;
    }
    return _mementos.removeLast();
  }
  
  int get size => _mementos.length;
}
