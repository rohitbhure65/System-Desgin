export interface Database {
  query(sql: string): void;
}

export class RealDatabase implements Database {
  query(sql: string): void {
    console.log(`Executing query: ${sql}`);
  }
}

export class DatabaseProxy implements Database {
  private realDatabase?: RealDatabase;
  private currentUser: string;
  private permissions: Map<string, boolean> = new Map();
  
  constructor(user: string) {
    this.currentUser = user;
    this.permissions.set('admin', true);
    this.permissions.set('user', false);
    this.permissions.set('guest', false);
  }
  
  private hasPermission(): boolean {
    return this.permissions.get(this.currentUser) ?? false;
  }
  
  query(sql: string): void {
    if (this.hasPermission()) {
      if (!this.realDatabase) {
        this.realDatabase = new RealDatabase();
      }
      this.realDatabase.query(sql);
    } else {
      console.log(`Access denied: User '${this.currentUser}' does not have permission to execute queries`);
    }
  }
  
  setUser(user: string): void {
    this.currentUser = user;
  }
}
