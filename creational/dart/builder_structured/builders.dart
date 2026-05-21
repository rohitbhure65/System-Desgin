import 'interfaces.dart';
import 'products.dart';

class SimpleHouseBuilder extends HouseBuilder {
  final House _house = House();
  
  @override
  void buildFoundation() => _house.setFoundation('Concrete foundation');
  
  @override
  void buildStructure() => _house.setStructure('Wood frame structure');
  
  @override
  void buildRoof() => _house.setRoof('Asphalt shingle roof');
  
  @override
  void buildInterior() => _house.setInterior('Basic interior with drywall');
  
  @override
  void buildGarage() => _house.setGarage(false);
  
  @override
  void buildGarden() => _house.setGarden(false);
  
  @override
  void buildSwimmingPool() => _house.setSwimmingPool(false);
  
  @override
  House getResult() => _house;
}

class LuxuryHouseBuilder extends HouseBuilder {
  final House _house = House();
  
  @override
  void buildFoundation() => _house.setFoundation('Reinforced concrete foundation with basement');
  
  @override
  void buildStructure() => _house.setStructure('Steel frame structure with brick exterior');
  
  @override
  void buildRoof() => _house.setRoof('Spanish tile roof with solar panels');
  
  @override
  void buildInterior() => _house.setInterior('Luxury interior with marble floors and custom cabinetry');
  
  @override
  void buildGarage() => _house.setGarage(true);
  
  @override
  void buildGarden() => _house.setGarden(true);
  
  @override
  void buildSwimmingPool() => _house.setSwimmingPool(true);
  
  @override
  House getResult() => _house;
}

class ComputerBuilder {
  final Computer _computer = Computer();
  
  ComputerBuilder setCpu(String cpu) {
    _computer.setCpu(cpu);
    return this;
  }
  
  ComputerBuilder setGpu(String gpu) {
    _computer.setGpu(gpu);
    return this;
  }
  
  ComputerBuilder setRam(int ram) {
    _computer.setRam(ram);
    return this;
  }
  
  ComputerBuilder setStorage(int storage) {
    _computer.setStorage(storage);
    return this;
  }
  
  ComputerBuilder addWifi() {
    _computer.setWifi(true);
    return this;
  }
  
  ComputerBuilder addBluetooth() {
    _computer.setBluetooth(true);
    return this;
  }
  
  Computer build() {
    return _computer;
  }
}

class SQLQueryBuilder {
  String _query = '';
  
  SQLQueryBuilder select(String columns) {
    _query = 'SELECT $columns';
    return this;
  }
  
  SQLQueryBuilder from(String table) {
    _query += ' FROM $table';
    return this;
  }
  
  SQLQueryBuilder where(String condition) {
    _query += ' WHERE $condition';
    return this;
  }
  
  SQLQueryBuilder orderBy(String column, {String direction = 'ASC'}) {
    _query += ' ORDER BY $column $direction';
    return this;
  }
  
  SQLQueryBuilder limit(int count) {
    _query += ' LIMIT $count';
    return this;
  }
  
  String build() {
    return '$_query;';
  }
}
