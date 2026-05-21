import { GUIFactory, DatabaseFactory, Button, Checkbox, IDatabaseConnection, DatabaseCommand } from './interfaces';
import { WindowsButton, WindowsCheckbox, MacButton, MacCheckbox, MySQLConnection, MySQLCommand, PostgreSQLConnection, PostgreSQLCommand } from './concrete_products';

export class WindowsFactory implements GUIFactory {
  createButton(): Button { return new WindowsButton(); }
  createCheckbox(): Checkbox { return new WindowsCheckbox(); }
}

export class MacFactory implements GUIFactory {
  createButton(): Button { return new MacButton(); }
  createCheckbox(): Checkbox { return new MacCheckbox(); }
}

export class MySQLFactory implements DatabaseFactory {
  createConnection(): IDatabaseConnection { return new MySQLConnection(); }
  createCommand(cmd: string): DatabaseCommand { return new MySQLCommand(cmd); }
}

export class PostgreSQLFactory implements DatabaseFactory {
  createConnection(): IDatabaseConnection { return new PostgreSQLConnection(); }
  createCommand(cmd: string): DatabaseCommand { return new PostgreSQLCommand(cmd); }
}
