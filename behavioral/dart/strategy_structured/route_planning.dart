import 'interfaces.dart';

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
