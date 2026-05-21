import 'interfaces.dart';

class ConcreteSoldierType extends SoldierType {
  @override
  final String uniform;
  @override
  final int speed;
  final String rank;
  
  ConcreteSoldierType(this.uniform, this.speed, this.rank);
  
  @override
  void render(int x, int y, String weapon) {
    print('Rendering $rank soldier at ($x, $y) with $uniform uniform, speed $speed, holding $weapon');
  }
}

class SoldierTypeFactory {
  final Map<String, SoldierType> _soldierTypes = {};
  
  String _getKey(String uniform, int speed, String rank) {
    return '$uniform|$speed|$rank';
  }
  
  SoldierType getSoldierType(String uniform, int speed, String rank) {
    var key = _getKey(uniform, speed, rank);
    
    if (!_soldierTypes.containsKey(key)) {
      print('Creating new soldier type: $rank');
      _soldierTypes[key] = ConcreteSoldierType(uniform, speed, rank);
    } else {
      print('Reusing existing soldier type: $rank');
    }
    
    return _soldierTypes[key]!;
  }
  
  int getTotalSoldierTypes() {
    return _soldierTypes.length;
  }
}

class Soldier {
  int x, y;
  final String weapon;
  final SoldierType soldierType;
  
  Soldier(this.x, this.y, this.weapon, this.soldierType);
  
  void render() {
    soldierType.render(x, y, weapon);
  }
  
  void move(int newX, int newY) {
    x = newX;
    y = newY;
  }
}
