abstract class Mediator {
  void sendMessage(String message, String sender);
}

abstract class Colleague {
  final Mediator _mediator;
  final String _name;
  
  Colleague(this._mediator, this._name);
  
  void send(String message) {
    _mediator.sendMessage(message, _name);
  }
  
  void receive(String message);
  
  String get name => _name;
}
