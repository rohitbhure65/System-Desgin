abstract class State {
  void insertCoin();
  void ejectCoin();
  void pressButton();
  void dispense();
}

abstract class AudioPlayerState {
  void clickPlay();
  void clickStop();
  void clickNext();
  void clickPrevious();
}
