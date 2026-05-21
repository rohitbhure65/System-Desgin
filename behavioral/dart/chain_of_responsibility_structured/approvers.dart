import 'interfaces.dart';

class TeamLead extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 1000) {
      print('TeamLead: Approved request of \$${amount}');
    } else {
      print('TeamLead: Amount exceeds limit, passing to manager...');
      passRequest(amount);
    }
  }
}

class ManagerApprover extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 5000) {
      print('Manager: Approved request of \$${amount}');
    } else {
      print('Manager: Amount exceeds limit, passing to director...');
      passRequest(amount);
    }
  }
}

class Director extends Approver {
  @override
  void approveRequest(double amount) {
    if (amount <= 20000) {
      print('Director: Approved request of \$${amount}');
    } else {
      print('Director: Amount exceeds limit, passing to CEO...');
      passRequest(amount);
    }
  }
}

class CEO extends Approver {
  @override
  void approveRequest(double amount) {
    print('CEO: Approved request of \$${amount} (final approver)');
  }
}
