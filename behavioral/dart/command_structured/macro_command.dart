import 'interfaces.dart';

class MacroCommand extends Command {
  final List<Command> _commands = [];
  
  void addCommand(Command command) {
    _commands.add(command);
  }
  
  @override
  void execute() {
    for (final command in _commands) {
      command.execute();
    }
  }
  
  @override
  void undo() {
    for (int i = _commands.length - 1; i >= 0; i--) {
      _commands[i].undo();
    }
  }
}
