import 'interfaces.dart';

class StockMarket {
  final List<StockObserver> _observers = [];
  final Map<String, double> _stockPrices = {};
  
  void addObserver(StockObserver observer) {
    _observers.add(observer);
  }
  
  void removeObserver(StockObserver observer) {
    _observers.remove(observer);
  }
  
  void updateStockPrice(String symbol, double price) {
    _stockPrices[symbol] = price;
    print('\n$symbol price updated to \$$price');
    _notifyObservers(symbol, price);
  }
  
  void _notifyObservers(String symbol, double price) {
    for (final observer in _observers) {
      observer.onStockPriceChange(symbol, price);
    }
  }
}

class Investor implements StockObserver {
  final String _name;
  final Map<String, int> _portfolio = {};
  
  Investor(this._name);
  
  void buyStock(String symbol, int shares) {
    _portfolio[symbol] = (_portfolio[symbol] ?? 0) + shares;
    print('$_name bought $shares shares of $symbol');
  }
  
  @override
  void onStockPriceChange(String symbol, double price) {
    final shares = _portfolio[symbol];
    if (shares != null && shares > 0) {
      print('  $_name owns $shares shares of $symbol (current price: \$$price)');
    }
  }
}

class TradingBot implements StockObserver {
  @override
  void onStockPriceChange(String symbol, double price) {
    print('  [TradingBot] Analyzing $symbol at \$$price');
    if (price > 100) {
      print('  [TradingBot] Recommendation: SELL');
    } else if (price < 50) {
      print('  [TradingBot] Recommendation: BUY');
    }
  }
}
