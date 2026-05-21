class GameStateMemento {
  final int level;
  final int health;
  final int score;
  final String position;
  
  GameStateMemento(this.level, this.health, this.score, this.position);
  
  int get getLevel => level;
  int get getHealth => health;
  int get getScore => score;
  String get getPosition => position;
}

class GameCharacter {
  int _level = 1;
  int _health = 100;
  int _score = 0;
  String _position = 'Start';
  
  void moveTo(String newPosition) {
    _position = newPosition;
    print('Moved to $_position');
  }
  
  void takeDamage(int damage) {
    _health -= damage;
    if (_health < 0) _health = 0;
    print('Took $damage damage. Health: $_health');
  }
  
  void gainScore(int points) {
    _score += points;
    print('Gained $points points. Score: $_score');
  }
  
  void levelUp() {
    _level++;
    _health = 100;
    print('Level up! Now at level $_level');
  }
  
  void displayStatus() {
    print('=== Character Status ===');
    print('Level: $_level');
    print('Health: $_health');
    print('Score: $_score');
    print('Position: $_position');
    print('=====================');
  }
  
  GameStateMemento saveState() {
    print('Saving game state...');
    return GameStateMemento(_level, _health, _score, _position);
  }
  
  void restoreState(GameStateMemento memento) {
    _level = memento.getLevel;
    _health = memento.getHealth;
    _score = memento.getScore;
    _position = memento.getPosition;
    print('Game state restored!');
    displayStatus();
  }
}

class GameSaveManager {
  final List<GameStateMemento> _saves = [];
  
  void createSave(GameStateMemento save) {
    _saves.add(save);
    print('Save created. Total saves: ${_saves.length}');
  }
  
  GameStateMemento? loadSave(int index) {
    if (index >= 0 && index < _saves.length) {
      print('Loading save ${index + 1}...');
      return _saves[index];
    }
    return null;
  }
  
  int get saveCount => _saves.length;
}
