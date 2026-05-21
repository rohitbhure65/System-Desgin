import 'interfaces.dart';

class PrototypeRegistry {
  final Map<String, Prototype> _prototypes = {};
  
  void registerPrototype(String key, Prototype prototype) {
    _prototypes[key] = prototype;
  }
  
  Prototype? clone(String key) {
    var prototype = _prototypes[key];
    return prototype?.clone();
  }
}
