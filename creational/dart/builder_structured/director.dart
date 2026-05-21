import 'interfaces.dart';

class ConstructionDirector {
  HouseBuilder? _builder;
  
  void setBuilder(HouseBuilder builder) {
    _builder = builder;
  }
  
  void buildBasicHouse() {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
  }
  
  void buildFullHouse() {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
    _builder!.buildGarage();
    _builder!.buildGarden();
    _builder!.buildSwimmingPool();
  }
  
  void buildCustomHouse(bool withGarage, bool withGarden, bool withPool) {
    _builder!.buildFoundation();
    _builder!.buildStructure();
    _builder!.buildRoof();
    _builder!.buildInterior();
    if (withGarage) _builder!.buildGarage();
    if (withGarden) _builder!.buildGarden();
    if (withPool) _builder!.buildSwimmingPool();
  }
}
