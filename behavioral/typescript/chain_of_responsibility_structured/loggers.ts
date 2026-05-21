import { Logger } from './interfaces';

export class ConsoleLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 1) {
      console.log(`[CONSOLE] ${message}`);
    }
    this.passLog(message, severity);
  }
}

export class FileLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 2) {
      console.log(`[FILE] ${message}`);
    }
    this.passLog(message, severity);
  }
}

export class ErrorLogger extends Logger {
  log(message: string, severity: number): void {
    if (severity >= 3) {
      console.log(`[ERROR] ${message}`);
    }
    this.passLog(message, severity);
  }
}
