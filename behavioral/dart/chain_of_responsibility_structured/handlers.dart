import 'interfaces.dart';

class SupportAgent extends Handler {
  @override
  void handle(String request) {
    if (request == 'technical_issue' || request == 'basic_question') {
      print('SupportAgent: Handling request - $request');
    } else {
      print('SupportAgent: Passing to next handler...');
      passRequest(request);
    }
  }
}

class TechnicalSpecialist extends Handler {
  @override
  void handle(String request) {
    if (request == 'complex_technical' || request == 'bug_report') {
      print('TechnicalSpecialist: Handling request - $request');
    } else {
      print('TechnicalSpecialist: Passing to next handler...');
      passRequest(request);
    }
  }
}

class Manager extends Handler {
  @override
  void handle(String request) {
    if (request == 'refund' || request == 'complaint' || request == 'escalation') {
      print('Manager: Handling request - $request');
    } else {
      print('Manager: Passing to next handler...');
      passRequest(request);
    }
  }
}
