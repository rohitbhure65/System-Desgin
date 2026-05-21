export interface Service {
  doWork(): void;
}

export class RealService implements Service {
  doWork(): void {
    console.log('Service: Performing work...');
  }
}

export class LoggingProxy implements Service {
  private realService: RealService;
  
  constructor() {
    this.realService = new RealService();
  }
  
  private log(message: string): void {
    console.log(`[LOG] ${message}`);
  }
  
  doWork(): void {
    this.log('Before doWork');
    this.realService.doWork();
    this.log('After doWork');
  }
}
