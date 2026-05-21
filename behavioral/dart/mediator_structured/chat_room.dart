import 'interfaces.dart';

class User extends Colleague {
  User(super.mediator, super.name);
  
  @override
  void receive(String message) {
    print('$_name received: $message');
  }
}

class Bot extends Colleague {
  Bot(super.mediator, super.name);
  
  @override
  void receive(String message) {
    print('$_name received: $message');
    send('Auto-reply: Thanks for your message!');
  }
}

class ChatRoom implements Mediator {
  final Map<String, Colleague> _colleagues = {};
  
  void addUser(Colleague colleague) {
    _colleagues[colleague.name] = colleague;
  }
  
  @override
  void sendMessage(String message, String sender) {
    print('$sender sends: $message');
    for (final entry in _colleagues.entries) {
      if (entry.key != sender) {
        entry.value.receive(message);
      }
    }
  }
}
