abstract class PaymentStrategy {
  void pay(double amount);
}

abstract class SortingStrategy {
  void sort(List<int> data);
}

abstract class RouteStrategy {
  void calculateRoute(String from, String to);
}
