abstract class GameCharacter {
  void createCharacter() {
    print('\n=== Creating Character ===');
    chooseName();
    selectRace();
    selectClass();
    assignStats();
    equipStartingItems();
    print('=== Character Created ===');
  }
  
  void chooseName();
  void selectRace();
  void selectClass();
  void assignStats();
  void equipStartingItems();
  
  void displayCharacter() {
    print('Character ready for adventure!');
  }
}

class Warrior extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Thorin');
  }
  
  @override
  void selectRace() {
    print('Race selected: Dwarf');
  }
  
  @override
  void selectClass() {
    print('Class selected: Warrior');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 18, DEX: 12, CON: 16, INT: 8, WIS: 10');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Iron Sword, Steel Shield, Chain Mail');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Battle Rage');
  }
}

class Mage extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Gandalf');
  }
  
  @override
  void selectRace() {
    print('Race selected: Human');
  }
  
  @override
  void selectClass() {
    print('Class selected: Mage');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 8, DEX: 14, CON: 10, INT: 18, WIS: 16');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Wooden Staff, Robe, Spellbook');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Fireball');
  }
}

class Rogue extends GameCharacter {
  @override
  void chooseName() {
    print('Name chosen: Legolas');
  }
  
  @override
  void selectRace() {
    print('Race selected: Elf');
  }
  
  @override
  void selectClass() {
    print('Class selected: Rogue');
  }
  
  @override
  void assignStats() {
    print('Stats assigned: STR: 12, DEX: 18, CON: 12, INT: 14, WIS: 12');
  }
  
  @override
  void equipStartingItems() {
    print('Equipped: Dagger, Leather Armor, Lockpicks');
  }
  
  @override
  void displayCharacter() {
    super.displayCharacter();
    print('Special ability: Stealth');
  }
}
