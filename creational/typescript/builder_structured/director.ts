import { HouseBuilder } from './interfaces';

export class ConstructionDirector {
  private builder: HouseBuilder | null = null;
  
  setBuilder(builder: HouseBuilder): void {
    this.builder = builder;
  }
  
  buildBasicHouse(): void {
    if (!this.builder) return;
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
  }
  
  buildFullHouse(): void {
    if (!this.builder) return;
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
    this.builder.buildGarage();
    this.builder.buildGarden();
    this.builder.buildSwimmingPool();
  }
  
  buildCustomHouse(withGarage: boolean, withGarden: boolean, withPool: boolean): void {
    if (!this.builder) return;
    this.builder.buildFoundation();
    this.builder.buildStructure();
    this.builder.buildRoof();
    this.builder.buildInterior();
    if (withGarage) this.builder.buildGarage();
    if (withGarden) this.builder.buildGarden();
    if (withPool) this.builder.buildSwimmingPool();
  }
}
