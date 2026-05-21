export interface State {
  insertCoin(): void;
  ejectCoin(): void;
  pressButton(): void;
  dispense(): void;
}

export interface AudioPlayerState {
  clickPlay(): void;
  clickStop(): void;
  clickNext(): void;
  clickPrevious(): void;
}
