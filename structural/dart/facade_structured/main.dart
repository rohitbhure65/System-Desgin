import 'facades.dart';

void main() {
  print('=== Facade Pattern Demo ===\n');
  
  print('--- Computer Boot Example ---');
  var computer = ComputerFacade();
  computer.start();
  print('');
  computer.shutdown();
  print('');
  
  print('--- Home Theater Example ---');
  var homeTheater = HomeTheaterFacade();
  homeTheater.watchMovie('The Matrix');
  homeTheater.endMovie();
  homeTheater.listenToRadio(98.7);
  homeTheater.turnOffRadio();
  print('');
  
  print('--- Order Processing Example ---');
  var orderSystem = OrderFacade();
  orderSystem.placeOrder('Laptop', 1, 999.99, '123 Main St', 'customer@email.com');
  orderSystem.cancelOrder('Laptop', 1, 999.99, 'customer@email.com');
}
