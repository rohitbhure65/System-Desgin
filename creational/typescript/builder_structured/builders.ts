import { HouseBuilder } from './interfaces';
import { House, Computer } from './products';

export class SimpleHouseBuilder implements HouseBuilder {
  private house: House = new House();
  
  buildFoundation(): void { this.house.setFoundation('Concrete foundation'); }
  buildStructure(): void { this.house.setStructure('Wood frame structure'); }
  buildRoof(): void { this.house.setRoof('Asphalt shingle roof'); }
  buildInterior(): void { this.house.setInterior('Basic interior with drywall'); }
  buildGarage(): void { this.house.setGarage(false); }
  buildGarden(): void { this.house.setGarden(false); }
  buildSwimmingPool(): void { this.house.setSwimmingPool(false); }
  getResult(): House { return this.house; }
}

export class LuxuryHouseBuilder implements HouseBuilder {
  private house: House = new House();
  
  buildFoundation(): void { this.house.setFoundation('Reinforced concrete foundation with basement'); }
  buildStructure(): void { this.house.setStructure('Steel frame structure with brick exterior'); }
  buildRoof(): void { this.house.setRoof('Spanish tile roof with solar panels'); }
  buildInterior(): void { this.house.setInterior('Luxury interior with marble floors and custom cabinetry'); }
  buildGarage(): void { this.house.setGarage(true); }
  buildGarden(): void { this.house.setGarden(true); }
  buildSwimmingPool(): void { this.house.setSwimmingPool(true); }
  getResult(): House { return this.house; }
}

export class ComputerBuilder {
  private computer: Computer = new Computer();
  
  setCpu(cpu: string): ComputerBuilder { this.computer.setCpu(cpu); return this; }
  setGpu(gpu: string): ComputerBuilder { this.computer.setGpu(gpu); return this; }
  setRam(ram: number): ComputerBuilder { this.computer.setRam(ram); return this; }
  setStorage(storage: number): ComputerBuilder { this.computer.setStorage(storage); return this; }
  addWifi(): ComputerBuilder { this.computer.setWifi(true); return this; }
  addBluetooth(): ComputerBuilder { this.computer.setBluetooth(true); return this; }
  build(): Computer { return this.computer; }
}

export class SQLQueryBuilder {
  private query: string = '';
  
  select(columns: string): SQLQueryBuilder { this.query = `SELECT ${columns}`; return this; }
  from(table: string): SQLQueryBuilder { this.query += ` FROM ${table}`; return this; }
  where(condition: string): SQLQueryBuilder { this.query += ` WHERE ${condition}`; return this; }
  orderBy(column: string, direction: string = 'ASC'): SQLQueryBuilder { this.query += ` ORDER BY ${column} ${direction}`; return this; }
  limit(count: number): SQLQueryBuilder { this.query += ` LIMIT ${count}`; return this; }
  build(): string { return `${this.query};`; }
}
