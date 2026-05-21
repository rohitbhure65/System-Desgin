abstract class Button {
  void click();
  void render();
  String get name;
}

abstract class Checkbox {
  void check();
  void render();
  String get name;
}

abstract class GUIFactory {
  Button createButton();
  Checkbox createCheckbox();
}

abstract class IDatabaseConnection {
  void connect();
  void disconnect();
  void executeQuery(String query);
}

abstract class DatabaseCommand {
  void execute();
}

abstract class DatabaseFactory {
  IDatabaseConnection createConnection();
  DatabaseCommand createCommand(String cmd);
}
