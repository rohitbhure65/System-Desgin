class Light {
  void on() {
    print('Light is ON');
  }
  
  void off() {
    print('Light is OFF');
  }
}

class Stereo {
  void on() {
    print('Stereo is ON');
  }
  
  void off() {
    print('Stereo is OFF');
  }
  
  void setVolume(int level) {
    print('Stereo volume set to $level');
  }
}

class BankAccount {
  double _balance = 0;
  
  BankAccount([double initialBalance = 0]) : _balance = initialBalance;
  
  void deposit(double amount) {
    _balance += amount;
    print('Deposited \$$amount. New balance: \$$_balance');
  }
  
  void withdraw(double amount) {
    if (_balance >= amount) {
      _balance -= amount;
      print('Withdrew \$$amount. New balance: \$$_balance');
    } else {
      print('Insufficient funds');
    }
  }
  
  double getBalance() => _balance;
}
