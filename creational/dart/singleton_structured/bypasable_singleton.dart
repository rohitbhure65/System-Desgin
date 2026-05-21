class BypasableSingleton {
  static final BypasableSingleton _instance = BypasableSingleton._internal();
  BypasableSingleton._internal();
  factory BypasableSingleton() => _instance;
}
