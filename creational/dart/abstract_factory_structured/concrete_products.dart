import 'interfaces.dart';

class WindowsButton extends Button {
  @override
  void click() => print('Windows button clicked!');
  @override
  void render() => print('Rendering Windows-style button...');
  @override
  String get name => 'Windows Button';
}

class WindowsCheckbox extends Checkbox {
  @override
  void check() => print('Windows checkbox checked!');
  @override
  void render() => print('Rendering Windows-style checkbox...');
  @override
  String get name => 'Windows Checkbox';
}

class MacButton extends Button {
  @override
  void click() => print('Mac button clicked!');
  @override
  void render() => print('Rendering Mac-style button...');
  @override
  String get name => 'Mac Button';
}

class MacCheckbox extends Checkbox {
  @override
  void check() => print('Mac checkbox checked!');
  @override
  void render() => print('Rendering Mac-style checkbox...');
  @override
  String get name => 'Mac Checkbox';
}

class MySQLConnection extends IDatabaseConnection {
  @override
  void connect() => print('Connecting to MySQL database...');
  @override
  void disconnect() => print('Disconnecting from MySQL database...');
  @override
  void executeQuery(String query) => print('Executing MySQL query: $query');
}

class MySQLCommand extends DatabaseCommand {
  final String _command;
  MySQLCommand(this._command);
  @override
  void execute() => print('Executing MySQL command: $_command');
}

class PostgreSQLConnection extends IDatabaseConnection {
  @override
  void connect() => print('Connecting to PostgreSQL database...');
  @override
  void disconnect() => print('Disconnecting from PostgreSQL database...');
  @override
  void executeQuery(String query) => print('Executing PostgreSQL query: $query');
}

class PostgreSQLCommand extends DatabaseCommand {
  final String _command;
  PostgreSQLCommand(this._command);
  @override
  void execute() => print('Executing PostgreSQL command: $_command');
}
