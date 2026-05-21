abstract class Handler {
  Handler? _nextHandler;
  
  Handler setNext(Handler handler) {
    _nextHandler = handler;
    return handler;
  }
  
  void handle(String request);
  
  void passRequest(String request) {
    _nextHandler?.handle(request);
  }
}

abstract class Approver {
  Approver? _nextApprover;
  
  Approver setNext(Approver approver) {
    _nextApprover = approver;
    return approver;
  }
  
  void approveRequest(double amount);
  
  void passRequest(double amount) {
    _nextApprover?.approveRequest(amount);
  }
}

abstract class Logger {
  Logger? _nextLogger;
  
  Logger setNext(Logger logger) {
    _nextLogger = logger;
    return logger;
  }
  
  void log(String message, int severity);
  
  void passLog(String message, int severity) {
    _nextLogger?.log(message, severity);
  }
}
