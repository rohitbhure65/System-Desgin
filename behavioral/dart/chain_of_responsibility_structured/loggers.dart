import 'interfaces.dart';

class ConsoleLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 1) {
      print('[CONSOLE] $message');
    }
    passLog(message, severity);
  }
}

class FileLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 2) {
      print('[FILE] $message');
    }
    passLog(message, severity);
  }
}

class ErrorLogger extends Logger {
  @override
  void log(String message, int severity) {
    if (severity >= 3) {
      print('[ERROR] $message');
    }
    passLog(message, severity);
  }
}
