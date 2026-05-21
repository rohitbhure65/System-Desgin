import 'interfaces.dart';
import 'receivers.dart';

class LightOnCommand extends Command {
  final Light _light;
  
  LightOnCommand(this._light);
  
  @override
  void execute() {
    _light.on();
  }
  
  @override
  void undo() {
    _light.off();
  }
}

class LightOffCommand extends Command {
  final Light _light;
  
  LightOffCommand(this._light);
  
  @override
  void execute() {
    _light.off();
  }
  
  @override
  void undo() {
    _light.on();
  }
}

class StereoOnCommand extends Command {
  final Stereo _stereo;
  int _previousVolume = 0;
  
  StereoOnCommand(this._stereo);
  
  @override
  void execute() {
    _stereo.on();
    _stereo.setVolume(10);
    _previousVolume = 10;
  }
  
  @override
  void undo() {
    _stereo.setVolume(_previousVolume);
    _stereo.off();
  }
}

class StereoOffCommand extends Command {
  final Stereo _stereo;
  
  StereoOffCommand(this._stereo);
  
  @override
  void execute() {
    _stereo.off();
  }
  
  @override
  void undo() {
    _stereo.on();
  }
}

class DepositCommand extends Command {
  final BankAccount _account;
  final double _amount;
  
  DepositCommand(this._account, this._amount);
  
  @override
  void execute() {
    _account.deposit(_amount);
  }
  
  @override
  void undo() {
    _account.withdraw(_amount);
  }
}

class WithdrawCommand extends Command {
  final BankAccount _account;
  final double _amount;
  bool _success = false;
  
  WithdrawCommand(this._account, this._amount);
  
  @override
  void execute() {
    final oldBalance = _account.getBalance();
    _account.withdraw(_amount);
    _success = _account.getBalance() < oldBalance;
  }
  
  @override
  void undo() {
    if (_success) {
      _account.deposit(_amount);
    }
  }
}
