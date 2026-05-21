import 'interfaces.dart';
import 'concrete_products.dart';

class WindowsFactory extends GUIFactory {
  @override
  Button createButton() => WindowsButton();
  @override
  Checkbox createCheckbox() => WindowsCheckbox();
}

class MacFactory extends GUIFactory {
  @override
  Button createButton() => MacButton();
  @override
  Checkbox createCheckbox() => MacCheckbox();
}

class MySQLFactory extends DatabaseFactory {
  @override
  IDatabaseConnection createConnection() => MySQLConnection();
  @override
  DatabaseCommand createCommand(String cmd) => MySQLCommand(cmd);
}

class PostgreSQLFactory extends DatabaseFactory {
  @override
  IDatabaseConnection createConnection() => PostgreSQLConnection();
  @override
  DatabaseCommand createCommand(String cmd) => PostgreSQLCommand(cmd);
}
