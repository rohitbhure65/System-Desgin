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
abstract class PaymentStrategy {
  void pay(double amount);
}

// Concrete Strategy 1: Credit Card
class CreditCardPayment implements PaymentStrategy {
  final String _cardNumber;
  final String _expiryDate;
  
  CreditCardPayment(this._cardNumber, this._expiryDate);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with Credit Card ending in ${_cardNumber.substring(_cardNumber.length - 4)}');
    print('  Card: ****-****-****-${_cardNumber.substring(_cardNumber.length - 4)}');
    print('  Expiry: $_expiryDate');
  }
}

// Concrete Strategy 2: PayPal
class PayPalPayment implements PaymentStrategy {
  final String _email;
  
  PayPalPayment(this._email);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with PayPal');
    print('  Account: $_email');
  }
}

// Concrete Strategy 3: Crypto
class CryptoPayment implements PaymentStrategy {
  final String _walletAddress;
  
  CryptoPayment(this._walletAddress);
  
  @override
  void pay(double amount) {
    print('Paying \$$amount with Cryptocurrency');
    print('  Wallet: ${_walletAddress.substring(0, 10)}...');
  }
}

// Context - uses the strategy
class ShoppingCart {
  PaymentStrategy? _paymentStrategy;
  final List<_Item> _items = [];
  
  void setPaymentStrategy(PaymentStrategy strategy) {
    _paymentStrategy = strategy;
  }
  
  void addItem(String item, double price) {
    _items.add(_Item(item, price));
  }
  
  double getTotal() {
    return _items.fold(0, (total, item) => total + item.price);
  }
  
  void checkout() {
    print('\n=== Checkout ===');
    print('Items:');
    for (final item in _items) {
      print('  - ${item.name}: \$${item.price}');
    }
    print('Total: \$${getTotal()}');
    
    if (_paymentStrategy != null) {
      _paymentStrategy!.pay(getTotal());
    } else {
      print('No payment method selected');
    }
  }
}

class _Item {
  final String name;
  final double price;
  
  _Item(this.name, this.price);
}

// Example 2: Sorting Strategies
// Shows how Strategy can be used for different algorithms

abstract class SortingStrategy {
  void sort(List<int> data);
}

class BubbleSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Bubble Sort...');
    final n = data.length;
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
        if (data[j] > data[j + 1]) {
          final temp = data[j];
          data[j] = data[j + 1];
          data[j + 1] = temp;
        }
      }
    }
  }
}

class QuickSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Quick Sort...');
    _quickSort(data, 0, data.length - 1);
  }
  
  void _quickSort(List<int> data, int low, int high) {
    if (low < high) {
      final pi = _partition(data, low, high);
      _quickSort(data, low, pi - 1);
      _quickSort(data, pi + 1, high);
    }
  }
  
  int _partition(List<int> data, int low, int high) {
    final pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
      if (data[j] < pivot) {
        i++;
        final temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
    final temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    return i + 1;
  }
}

class MergeSort implements SortingStrategy {
  @override
  void sort(List<int> data) {
    print('Using Merge Sort...');
    _mergeSort(data, 0, data.length - 1);
  }
  
  void _mergeSort(List<int> data, int left, int right) {
    if (left < right) {
      final mid = left + (right - left) ~/ 2;
      _mergeSort(data, left, mid);
      _mergeSort(data, mid + 1, right);
      _merge(data, left, mid, right);
    }
  }
  
  void _merge(List<int> data, int left, int mid, int right) {
    final n1 = mid - left + 1;
    final n2 = right - mid;
    
    final L = data.sublist(left, left + n1);
    final R = data.sublist(mid + 1, mid + 1 + n2);
    
    int i = 0, j = 0, k = left;
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
  SortingStrategy? _strategy;
  
  void setSortingStrategy(SortingStrategy strategy) {
    _strategy = strategy;
  }
  
  void sortData(List<int> data) {
    print('\nOriginal data: ${data.join(' ')}');
    
    if (_strategy != null) {
      _strategy!.sort(data);
    } else {
      print('No sorting strategy selected');
    }
    
    print('Sorted data: ${data.join(' ')}');
  }
}

// Example 3: Route Planning Strategies
// Shows how Strategy can be used for navigation

abstract class RouteStrategy {
  void calculateRoute(String from, String to);
}

class FastestRoute implements RouteStrategy {
  @override
  void calculateRoute(String from, String to) {
    print('Calculating fastest route from $from to $to');
    print('  Using highways and main roads to minimize time');
    print('  Estimated time: 25 minutes');
  }
}

class ShortestRoute implements RouteStrategy {
  @override
  void calculateRoute(String from, String to) {
    print('Calculating shortest route from $from to $to');
    print('  Using direct path to minimize distance');
    print('  Estimated distance: 15 km');
  }
}

class ScenicRoute implements RouteStrategy {
  @override
  void calculateRoute(String from, String to) {
    print('Calculating scenic route from $from to $to');
    print('  Using parks and landmarks for best views');
    print('  Estimated time: 45 minutes');
  }
}

class NavigationSystem {
  RouteStrategy? _strategy;
  
  void setRouteStrategy(RouteStrategy strategy) {
    _strategy = strategy;
  }
  
  void navigate(String from, String to) {
    print('\n=== Navigation ===');
    print('From: $from');
    print('To: $to');
    
    if (_strategy != null) {
      _strategy!.calculateRoute(from, to);
    } else {
      print('No route strategy selected');
    }
  }
}

// Demo code
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
