import 'interfaces.dart';

class RemoteControl {
  final List<Command> _commandHistory = [];
  final List<Command> _undoStack = [];
  
  void setCommand(Command command) {
    _commandHistory.add(command);
  }
  
  void buttonPressed(int slot) {
    if (slot < _commandHistory.length) {
      _commandHistory[slot].execute();
      _undoStack.add(_commandHistory[slot]);
    }
  }
  
  void undoButtonPressed() {
    if (_undoStack.isNotEmpty) {
      final command = _undoStack.removeLast();
      command.undo();
    } else {
      print('Nothing to undo');
    }
  }
}
