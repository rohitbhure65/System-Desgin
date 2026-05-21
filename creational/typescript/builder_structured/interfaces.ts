import { House, Computer } from './products';

export interface HouseBuilder {
  buildFoundation(): void;
  buildStructure(): void;
  buildRoof(): void;
  buildInterior(): void;
  buildGarage(): void;
  buildGarden(): void;
  buildSwimmingPool(): void;
  getResult(): House;
}

export interface ComputerBuilder {
  buildCPU(): void;
  buildMotherboard(): void;
  buildRAM(): void;
  buildStorage(): void;
  buildGPU(): void;
  buildPowerSupply(): void;
  buildCase(): void;
  buildPeripherals(): void;
  getResult(): Computer;
}

