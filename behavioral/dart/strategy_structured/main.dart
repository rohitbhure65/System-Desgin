import 'interfaces.dart';
import 'payment.dart';
import 'sorting.dart';
import 'route_planning.dart';

void main() {
  print('=== Strategy Pattern Demo ===\n');
  
  // Example 1: Payment Processing
  print('--- Payment Processing Example ---');
  
  final cart = ShoppingCart();
  cart.addItem('Laptop', 999.99);
  cart.addItem('Mouse', 29.99);
  cart.addItem('Keyboard', 79.99);
  
  print('\nPaying with Credit Card:');
  cart.setPaymentStrategy(CreditCardPayment('4111111111111111', '12/25'));
  cart.checkout();
  
  print('\nPaying with PayPal:');
  cart.setPaymentStrategy(PayPalPayment('user@example.com'));
  cart.checkout();
  
  print('\nPaying with Crypto:');
  cart.setPaymentStrategy(CryptoPayment('0x1234567890abcdef'));
  cart.checkout();
  
  // Example 2: Sorting Algorithms
  print('\n--- Sorting Algorithms Example ---');
  
  final sorter = Sorter();
  final data = [64, 34, 25, 12, 22, 11, 90];
  
  sorter.setSortingStrategy(BubbleSort());
  sorter.sortData(List.from(data));
  
  sorter.setSortingStrategy(QuickSort());
  sorter.sortData(List.from(data));
  
  sorter.setSortingStrategy(MergeSort());
  sorter.sortData(List.from(data));
  
  // Example 3: Route Planning
  print('\n--- Route Planning Example ---');
  
  final nav = NavigationSystem();
  
  print('\nFastest route:');
  nav.setRouteStrategy(FastestRoute());
  nav.navigate('Home', 'Office');
  
  print('\nShortest route:');
  nav.setRouteStrategy(ShortestRoute());
  nav.navigate('Home', 'Office');
  
  print('\nScenic route:');
  nav.setRouteStrategy(ScenicRoute());
  nav.navigate('Home', 'Office');
}
