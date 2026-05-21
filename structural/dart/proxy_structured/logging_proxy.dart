abstract class Service {
  void doWork();
}

class RealService extends Service {
  @override
  void doWork() {
    print('Service: Performing work...');
  }
}

class LoggingProxy extends Service {
  final RealService _realService = RealService();
  
  void _log(String message) {
    print('[LOG] $message');
  }
  
  @override
  void doWork() {
    _log('Before doWork');
    _realService.doWork();
    _log('After doWork');
  }
}
