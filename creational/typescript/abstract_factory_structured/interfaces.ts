export interface Button {
  click(): void;
  render(): void;
  getName(): string;
}

export interface Checkbox {
  check(): void;
  render(): void;
  getName(): string;
}

export interface GUIFactory {
  createButton(): Button;
  createCheckbox(): Checkbox;
}

export interface IDatabaseConnection {
  connect(): void;
  disconnect(): void;
  executeQuery(query: string): void;
}

export interface DatabaseCommand {
  execute(): void;
}

export interface DatabaseFactory {
  createConnection(): IDatabaseConnection;
  createCommand(cmd: string): DatabaseCommand;
}
