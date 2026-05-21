import 'interfaces.dart';

class VendingMachine {
  late State _currentState;
  int _coinCount = 0;
  int _stockCount;
  
  VendingMachine(this._stockCount) {
    if (_stockCount > 0) {
      _currentState = NoCoinState(this);
    } else {
      _currentState = SoldOutState(this);
    }
  }
  
  void setState(State state) {
    _currentState = state;
  }
  
  void insertCoin() {
    _currentState.insertCoin();
  }
  
  void ejectCoin() {
    _currentState.ejectCoin();
  }
  
  void pressButton() {
    _currentState.pressButton();
  }
  
  void dispense() {
    _currentState.dispense();
  }
  
  void addCoin() {
    _coinCount++;
    print('Coin inserted. Total coins: $_coinCount');
  }
  
  void returnCoin() {
    if (_coinCount > 0) {
      _coinCount--;
      print('Coin returned. Total coins: $_coinCount');
    }
  }
  
  void releaseProduct() {
    if (_stockCount > 0) {
      _stockCount--;
      _coinCount--;
      print('Product dispensed. Stock: $_stockCount, Coins: $_coinCount');
    }
  }
  
  int get coinCount => _coinCount;
  int get stockCount => _stockCount;
}

class NoCoinState implements State {
  final VendingMachine _machine;
  
  NoCoinState(this._machine);
  
  @override
  void insertCoin() {
    print('Coin inserted...');
    _machine.addCoin();
    _machine.setState(HasCoinState(_machine));
  }
  
  @override
  void ejectCoin() {
    print('No coin to eject');
  }
  
  @override
  void pressButton() {
    print('Please insert a coin first');
  }
  
  @override
  void dispense() {
    print('Please insert a coin first');
  }
}

class HasCoinState implements State {
  final VendingMachine _machine;
  
  HasCoinState(this._machine);
  
  @override
  void insertCoin() {
    print('Coin already inserted');
  }
  
  @override
  void ejectCoin() {
    print('Coin ejected');
    _machine.returnCoin();
    _machine.setState(NoCoinState(_machine));
  }
  
  @override
  void pressButton() {
    print('Button pressed...');
    if (_machine.stockCount > 0) {
      _machine.setState(DispensingState(_machine));
      _machine.dispense();
    } else {
      print('Out of stock');
      _machine.setState(SoldOutState(_machine));
    }
  }
  
  @override
  void dispense() {
    print('Press button to dispense');
  }
}

class DispensingState implements State {
  final VendingMachine _machine;
  
  DispensingState(this._machine);
  
  @override
  void insertCoin() {
    print('Please wait, dispensing...');
  }
  
  @override
  void ejectCoin() {
    print('Cannot eject during dispensing');
  }
  
  @override
  void pressButton() {
    print('Already dispensing...');
  }
  
  @override
  void dispense() {
    _machine.releaseProduct();
    if (_machine.stockCount > 0) {
      _machine.setState(NoCoinState(_machine));
    } else {
      _machine.setState(SoldOutState(_machine));
    }
  }
}

class SoldOutState implements State {
  SoldOutState(VendingMachine machine);
  
  @override
  void insertCoin() {
    print('Cannot insert coin, machine is sold out');
  }
  
  @override
  void ejectCoin() {
    print('Cannot eject, no coin inserted');
  }
  
  @override
  void pressButton() {
    print('Machine is sold out');
  }
  
  @override
  void dispense() {
    print('Machine is sold out');
  }
}
