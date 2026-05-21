import 'products.dart';

abstract class HouseBuilder {
  void buildFoundation();
  void buildStructure();
  void buildRoof();
  void buildInterior();
  void buildGarage();
  void buildGarden();
  void buildSwimmingPool();
  House getResult();
}
