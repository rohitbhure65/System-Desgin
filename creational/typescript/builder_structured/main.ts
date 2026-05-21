import { ConstructionDirector } from './director';
import { SimpleHouseBuilder, LuxuryHouseBuilder, ComputerBuilder, SQLQueryBuilder } from './builders';

function demoBuilder(): void {
  console.log('=== Builder Pattern Demo ===\n');
  
  console.log('--- Classic Builder with Director ---');
  
  const director = new ConstructionDirector();
  
  console.log('\nBuilding Simple House:');
  const simpleBuilder = new SimpleHouseBuilder();
  director.setBuilder(simpleBuilder);
  director.buildBasicHouse();
  const simpleHouse = simpleBuilder.getResult();
  simpleHouse.display();
  
  console.log('\nBuilding Luxury House:');
  const luxuryBuilder = new LuxuryHouseBuilder();
  director.setBuilder(luxuryBuilder);
  director.buildFullHouse();
  const luxuryHouse = luxuryBuilder.getResult();
  luxuryHouse.display();
  
  console.log('\nBuilding Custom House (with garage and garden, no pool):');
  const customBuilder = new SimpleHouseBuilder();
  director.setBuilder(customBuilder);
  director.buildCustomHouse(true, true, false);
  const customHouse = customBuilder.getResult();
  customHouse.display();
  
  console.log('\n--- Fluent Builder (Method Chaining) ---');
  
  console.log('\nBuilding Gaming Computer:');
  const gamingComputer = new ComputerBuilder()
      .setCpu('Intel Core i9-13900K')
      .setGpu('NVIDIA RTX 4090')
      .setRam(32)
      .setStorage(1000)
      .addWifi()
      .addBluetooth()
      .build();
  gamingComputer.display();
  
  console.log('\nBuilding Office Computer:');
  const officeComputer = new ComputerBuilder()
      .setCpu('Intel Core i5-13400')
      .setGpu('Integrated Graphics')
      .setRam(16)
      .setStorage(512)
      .addWifi()
      .build();
  officeComputer.display();
  
  console.log('\n--- SQL Query Builder ---');
  
  const query1 = new SQLQueryBuilder()
      .select('*')
      .from('users')
      .where('age > 18')
      .orderBy('name', 'ASC')
      .limit(10)
      .build();
  console.log(`Query 1: ${query1}`);
  
  const query2 = new SQLQueryBuilder()
      .select('name, email')
      .from('customers')
      .where('active = true')
      .orderBy('created_at', 'DESC')
      .build();
  console.log(`Query 2: ${query2}`);
}

demoBuilder();
