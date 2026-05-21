export class Logger {
  private static _instance: Logger | null = null;
  private logCount: number = 0;
  
  private constructor() {
    console.log('Logger: Initializing logger...');
  }
  
  public static get instance(): Logger {
    if (!Logger._instance) {
      Logger._instance = new Logger();
    }
    return Logger._instance;
  }
  
  public log(message: string): void {
    this.logCount++;
    console.log(`[LOG #${this.logCount}] ${message}`);
  }
  
  public getLogCount(): number { return this.logCount; }
}
