import { CreditCardPayment, PayPalPayment, CryptoPayment, ShoppingCart } from './payment';
import { BubbleSort, QuickSort, MergeSort, Sorter } from './sorting';
import { FastestRoute, ShortestRoute, ScenicRoute, NavigationSystem } from './route_planning';

console.log('=== Strategy Pattern Demo ===\n');

// Example 1: Payment Processing
console.log('--- Payment Processing Example ---');

const cart = new ShoppingCart();
cart.addItem('Laptop', 999.99);
cart.addItem('Mouse', 29.99);
cart.addItem('Keyboard', 79.99);

console.log('\nPaying with Credit Card:');
cart.setPaymentStrategy(new CreditCardPayment('4111111111111111', '12/25', '123'));
cart.checkout();

console.log('\nPaying with PayPal:');
cart.setPaymentStrategy(new PayPalPayment('user@example.com', 'password'));
cart.checkout();

console.log('\nPaying with Crypto:');
cart.setPaymentStrategy(new CryptoPayment('0x1234567890abcdef', 'private_key'));
cart.checkout();

// Example 2: Sorting Algorithms
console.log('\n--- Sorting Algorithms Example ---');

const sorter = new Sorter();
const data = [64, 34, 25, 12, 22, 11, 90];

sorter.setSortingStrategy(new BubbleSort());
sorter.sortData([...data]);

sorter.setSortingStrategy(new QuickSort());
sorter.sortData([...data]);

sorter.setSortingStrategy(new MergeSort());
sorter.sortData([...data]);

// Example 3: Route Planning
console.log('\n--- Route Planning Example ---');

const nav = new NavigationSystem();

console.log('\nFastest route:');
nav.setRouteStrategy(new FastestRoute());
nav.navigate('Home', 'Office');

console.log('\nShortest route:');
nav.setRouteStrategy(new ShortestRoute());
nav.navigate('Home', 'Office');

console.log('\nScenic route:');
nav.setRouteStrategy(new ScenicRoute());
nav.navigate('Home', 'Office');
