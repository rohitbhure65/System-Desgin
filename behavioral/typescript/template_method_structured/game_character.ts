export abstract class GameCharacter {
  createCharacter(): void {
    console.log('\n=== Creating Character ===');
    this.chooseName();
    this.selectRace();
    this.selectClass();
    this.assignStats();
    this.equipStartingItems();
    console.log('=== Character Created ===');
  }
  
  protected abstract chooseName(): void;
  protected abstract selectRace(): void;
  protected abstract selectClass(): void;
  protected abstract assignStats(): void;
  protected abstract equipStartingItems(): void;
  
  protected displayCharacter(): void {
    console.log('Character ready for adventure!');
  }
}

export class Warrior extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Thorin');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Dwarf');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Warrior');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Iron Sword, Steel Shield, Chain Mail');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Battle Rage');
  }
}

export class Mage extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Gandalf');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Human');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Mage');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Wooden Staff, Robe, Spellbook');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Fireball');
  }
}

export class Rogue extends GameCharacter {
  protected chooseName(): void {
    console.log('Name chosen: Legolas');
  }
  
  protected selectRace(): void {
    console.log('Race selected: Elf');
  }
  
  protected selectClass(): void {
    console.log('Class selected: Rogue');
  }
  
  protected assignStats(): void {
    console.log('Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12');
  }
  
  protected equipStartingItems(): void {
    console.log('Equipped: Dagger, Leather Armor, Lockpicks');
  }
  
  protected displayCharacter(): void {
    super.displayCharacter();
    console.log('Special ability: Stealth');
  }
}
