export class DatabaseConnection {
  private static instance: DatabaseConnection | null = null;
  
  private isConnected: boolean = false;
  private queryCount: number = 0;
  
  private constructor() {
    console.log('DatabaseConnection: Initializing connection...');
    this.isConnected = true;
  }
  
  public static getInstance(): DatabaseConnection {
    if (!DatabaseConnection.instance) {
      DatabaseConnection.instance = new DatabaseConnection();
    }
    return DatabaseConnection.instance;
  }
  
  public executeQuery(query: string): void {
    if (this.isConnected) {
      this.queryCount++;
      console.log(`Executing query #${this.queryCount}: ${query}`);
    } else {
      console.log('Error: Not connected to database');
    }
  }
  
  public getQueryCount(): number { return this.queryCount; }
  public getConnectionStatus(): boolean { return this.isConnected; }
}
