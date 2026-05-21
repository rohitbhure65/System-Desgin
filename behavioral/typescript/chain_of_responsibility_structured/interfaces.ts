export abstract class Handler {
  protected nextHandler: Handler | null = null;
  
  setNext(handler: Handler): Handler {
    this.nextHandler = handler;
    return handler;
  }
  
  abstract handle(request: string): void;
  
  protected passRequest(request: string): void {
    if (this.nextHandler) {
      this.nextHandler.handle(request);
    } else {
      console.log('Request could not be handled');
    }
  }
}

export abstract class Approver {
  protected nextApprover: Approver | null = null;
  
  setNext(approver: Approver): Approver {
    this.nextApprover = approver;
    return approver;
  }
  
  abstract approveRequest(amount: number): void;
  
  protected passRequest(amount: number): void {
    if (this.nextApprover) {
      this.nextApprover.approveRequest(amount);
    } else {
      console.log('Request cannot be approved');
    }
  }
}

export abstract class Logger {
  protected nextLogger: Logger | null = null;
  
  setNext(logger: Logger): Logger {
    this.nextLogger = logger;
    return logger;
  }
  
  abstract log(message: string, severity: number): void;
  
  protected passLog(message: string, severity: number): void {
    if (this.nextLogger) {
      this.nextLogger.log(message, severity);
    }
  }
}
