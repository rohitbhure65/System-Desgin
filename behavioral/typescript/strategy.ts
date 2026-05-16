/*
 * STRATEGY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
 * It lets the algorithm vary independently from clients that use it.
 * 
 * WHY DOES IT EXIST?
 * - When you want to define a family of algorithms and make them interchangeable
 * - When you want to avoid conditional statements for selecting algorithms
 * - When you want to separate algorithm implementation from the code that uses it
 * 
 * WHEN TO USE IT?
 * - When you have multiple ways to do an operation and want to switch between them at runtime
 * - When you want to isolate the algorithm implementation from the client code
 * - When you have complex conditional logic that selects different algorithms
 * - Common use cases: sorting algorithms, payment processing, compression, route planning, validation
 * 
 * PROS:
 * - Open/Closed Principle (can add new strategies without changing existing code)
 * - Separates algorithm implementation from the code that uses it
 * - Eliminates conditional statements for selecting algorithms
 * - Allows runtime selection of algorithms
 * 
 * CONS:
 * - Clients must be aware of the differences between strategies
 * - Can increase the number of classes in the system
 * - May lead to performance overhead if strategies are complex
 * - Can make the code more complex for simple scenarios
 * 
 * REAL-WORLD ANALOGY:
 * Think of a GPS navigation app. It can use different route calculation strategies: fastest route, shortest distance, avoid highways, scenic route. You can switch between these strategies at runtime without changing the app itself. The app (context) delegates the route calculation to the selected strategy.
 */

// Strategy interface - declares the algorithm method
interface PaymentStrategy {
  pay(amount: number): void;
}

// Concrete Strategy 1: Credit Card
class CreditCardPayment implements PaymentStrategy {
  private cardNumber: string;
  private expiryDate: string;
  private cvv: string;
  
  constructor(card: string, expiry: string, cvv: string) {
    this.cardNumber = card;
    this.expiryDate = expiry;
    this.cvv = cvv;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with Credit Card ending in ${this.cardNumber.slice(-4)}`);
    console.log(`  Card: ****-****-****-${this.cardNumber.slice(-4)}`);
    console.log(`  Expiry: ${this.expiryDate}`);
  }
}

// Concrete Strategy 2: PayPal
class PayPalPayment implements PaymentStrategy {
  private email: string;
  private password: string;
  
  constructor(email: string, password: string) {
    this.email = email;
    this.password = password;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with PayPal`);
    console.log(`  Account: ${this.email}`);
  }
}

// Concrete Strategy 3: Crypto
class CryptoPayment implements PaymentStrategy {
  private walletAddress: string;
  private privateKey: string;
  
  constructor(wallet: string, key: string) {
    this.walletAddress = wallet;
    this.privateKey = key;
  }
  
  pay(amount: number): void {
    console.log(`Paying $${amount} with Cryptocurrency`);
    console.log(`  Wallet: ${this.walletAddress.slice(0, 10)}...`);
  }
}

// Context - uses the strategy
class ShoppingCart {
  private paymentStrategy: PaymentStrategy | null = null;
  private items: { name: string; price: number }[] = [];
  
  setPaymentStrategy(strategy: PaymentStrategy): void {
    this.paymentStrategy = strategy;
  }
  
  addItem(item: string, price: number): void {
    this.items.push({ name: item, price: price });
  }
  
  getTotal(): number {
    return this.items.reduce((total, item) => total + item.price, 0);
  }
  
  checkout(): void {
    console.log('\n=== Checkout ===');
    console.log('Items:');
    for (const item of this.items) {
      console.log(`  - ${item.name}: $${item.price}`);
    }
    console.log(`Total: $${this.getTotal()}`);
    
    if (this.paymentStrategy) {
      this.paymentStrategy.pay(this.getTotal());
    } else {
      console.log('No payment method selected');
    }
  }
}

// Example 2: Sorting Strategies
// Shows how Strategy can be used for different algorithms

interface SortingStrategy {
  sort(data: number[]): void;
}

class BubbleSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Bubble Sort...');
    const n = data.length;
    for (let i = 0; i < n - 1; i++) {
      for (let j = 0; j < n - i - 1; j++) {
        if (data[j] > data[j + 1]) {
          [data[j], data[j + 1]] = [data[j + 1], data[j]];
        }
      }
    }
  }
}

class QuickSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Quick Sort...');
    this.quickSort(data, 0, data.length - 1);
  }
  
  private quickSort(data: number[], low: number, high: number): void {
    if (low < high) {
      const pi = this.partition(data, low, high);
      this.quickSort(data, low, pi - 1);
      this.quickSort(data, pi + 1, high);
    }
  }
  
  private partition(data: number[], low: number, high: number): number {
    const pivot = data[high];
    let i = low - 1;
    for (let j = low; j < high; j++) {
      if (data[j] < pivot) {
        i++;
        [data[i], data[j]] = [data[j], data[i]];
      }
    }
    [data[i + 1], data[high]] = [data[high], data[i + 1]];
    return i + 1;
  }
}

class MergeSort implements SortingStrategy {
  sort(data: number[]): void {
    console.log('Using Merge Sort...');
    this.mergeSort(data, 0, data.length - 1);
  }
  
  private mergeSort(data: number[], left: number, right: number): void {
    if (left < right) {
      const mid = left + Math.floor((right - left) / 2);
      this.mergeSort(data, left, mid);
      this.mergeSort(data, mid + 1, right);
      this.merge(data, left, mid, right);
    }
  }
  
  private merge(data: number[], left: number, mid: number, right: number): void {
    const n1 = mid - left + 1;
    const n2 = right - mid;
    
    const L = data.slice(left, left + n1);
    const R = data.slice(mid + 1, mid + 1 + n2);
    
    let i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        data[k++] = L[i++];
      } else {
        data[k++] = R[j++];
      }
    }
    
    while (i < n1) data[k++] = L[i++];
    while (j < n2) data[k++] = R[j++];
  }
}

class Sorter {
  private strategy: SortingStrategy | null = null;
  
  setSortingStrategy(strategy: SortingStrategy): void {
    this.strategy = strategy;
  }
  
  sortData(data: number[]): void {
    console.log('\nOriginal data: ' + data.join(' '));
    
    if (this.strategy) {
      this.strategy.sort(data);
    } else {
      console.log('No sorting strategy selected');
    }
    
    console.log('Sorted data: ' + data.join(' '));
  }
}

// Example 3: Route Planning Strategies
// Shows how Strategy can be used for navigation

interface RouteStrategy {
  calculateRoute(from: string, to: string): void;
}

class FastestRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating fastest route from ${from} to ${to}`);
    console.log('  Using highways and main roads to minimize time');
    console.log('  Estimated time: 25 minutes');
  }
}

class ShortestRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating shortest route from ${from} to ${to}`);
    console.log('  Using direct path to minimize distance');
    console.log('  Estimated distance: 15 km');
  }
}

class ScenicRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating scenic route from ${from} to ${to}`);
    console.log('  Using parks and landmarks for best views');
    console.log('  Estimated time: 45 minutes');
  }
}

class NavigationSystem {
  private strategy: RouteStrategy | null = null;
  
  setRouteStrategy(strategy: RouteStrategy): void {
    this.strategy = strategy;
  }
  
  navigate(from: string, to: string): void {
    console.log('\n=== Navigation ===');
    console.log(`From: ${from}`);
    console.log(`To: ${to}`);
    
    if (this.strategy) {
      this.strategy.calculateRoute(from, to);
    } else {
      console.log('No route strategy selected');
    }
  }
}

// Demo code
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
