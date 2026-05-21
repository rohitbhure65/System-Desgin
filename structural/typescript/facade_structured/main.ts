import { ComputerFacade, HomeTheaterFacade, OrderFacade } from './facades';

function demoFacade(): void {
  console.log('=== Facade Pattern Demo ===\n');
  
  console.log('--- Computer Boot Example ---');
  const computer = new ComputerFacade();
  computer.start();
  console.log();
  computer.shutdown();
  console.log();
  
  console.log('--- Home Theater Example ---');
  const homeTheater = new HomeTheaterFacade();
  homeTheater.watchMovie('The Matrix');
  homeTheater.endMovie();
  homeTheater.listenToRadio(98.7);
  homeTheater.turnOffRadio();
  console.log();
  
  console.log('--- Order Processing Example ---');
  const orderSystem = new OrderFacade();
  orderSystem.placeOrder('Laptop', 1, 999.99, '123 Main St', 'customer@email.com');
  orderSystem.cancelOrder('Laptop', 1, 999.99, 'customer@email.com');
}

demoFacade();
