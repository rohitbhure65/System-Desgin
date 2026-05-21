import { Button, Checkbox, IDatabaseConnection, DatabaseCommand } from './interfaces';

export class WindowsButton implements Button {
  click(): void { console.log('Windows button clicked!'); }
  render(): void { console.log('Rendering Windows-style button...'); }
  getName(): string { return 'Windows Button'; }
}

export class WindowsCheckbox implements Checkbox {
  check(): void { console.log('Windows checkbox checked!'); }
  render(): void { console.log('Rendering Windows-style checkbox...'); }
  getName(): string { return 'Windows Checkbox'; }
}

export class MacButton implements Button {
  click(): void { console.log('Mac button clicked!'); }
  render(): void { console.log('Rendering Mac-style button...'); }
  getName(): string { return 'Mac Button'; }
}

export class MacCheckbox implements Checkbox {
  check(): void { console.log('Mac checkbox checked!'); }
  render(): void { console.log('Rendering Mac-style checkbox...'); }
  getName(): string { return 'Mac Checkbox'; }
}

export class MySQLConnection implements IDatabaseConnection {
  connect(): void { console.log('Connecting to MySQL database...'); }
  disconnect(): void { console.log('Disconnecting from MySQL database...'); }
  executeQuery(query: string): void { console.log(`Executing MySQL query: ${query}`); }
}

export class MySQLCommand implements DatabaseCommand {
  constructor(private command: string) {}
  execute(): void { console.log(`Executing MySQL command: ${this.command}`); }
}

export class PostgreSQLConnection implements IDatabaseConnection {
  connect(): void { console.log('Connecting to PostgreSQL database...'); }
  disconnect(): void { console.log('Disconnecting from PostgreSQL database...'); }
  executeQuery(query: string): void { console.log(`Executing PostgreSQL query: ${query}`); }
}

export class PostgreSQLCommand implements DatabaseCommand {
  constructor(private command: string) {}
  execute(): void { console.log(`Executing PostgreSQL command: ${this.command}`); }
}
