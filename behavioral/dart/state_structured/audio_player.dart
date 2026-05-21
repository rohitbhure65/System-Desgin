import 'interfaces.dart';

class AudioPlayer {
  late AudioPlayerState _currentState;
  bool _isPlaying = false;
  int _currentTrack = 1;
  int _totalTracks;
  
  AudioPlayer(this._totalTracks) {
    _currentState = StoppedState(this);
  }
  
  void setState(AudioPlayerState state) {
    _currentState = state;
  }
  
  void clickPlay() {
    _currentState.clickPlay();
  }
  
  void clickStop() {
    _currentState.clickStop();
  }
  
  void clickNext() {
    _currentState.clickNext();
  }
  
  void clickPrevious() {
    _currentState.clickPrevious();
  }
  
  void startPlaying() {
    _isPlaying = true;
    print('Started playing track $_currentTrack');
  }
  
  void stopPlaying() {
    _isPlaying = false;
    print('Stopped playing');
  }
  
  void nextTrack() {
    _currentTrack = (_currentTrack % _totalTracks) + 1;
    print('Moved to track $_currentTrack');
  }
  
  void previousTrack() {
    _currentTrack = _currentTrack == 1 ? _totalTracks : _currentTrack - 1;
    print('Moved to track $_currentTrack');
  }
  
  bool get isPlaying => _isPlaying;
}

class PlayingState implements AudioPlayerState {
  final AudioPlayer _player;
  
  PlayingState(this._player);
  
  @override
  void clickPlay() {
    print('Already playing');
  }
  
  @override
  void clickStop() {
    print('Stopping playback...');
    _player.stopPlaying();
    _player.setState(StoppedState(_player));
  }
  
  @override
  void clickNext() {
    print('Skipping to next track...');
    _player.nextTrack();
  }
  
  @override
  void clickPrevious() {
    print('Going to previous track...');
    _player.previousTrack();
  }
}

class StoppedState implements AudioPlayerState {
  final AudioPlayer _player;
  
  StoppedState(this._player);
  
  @override
  void clickPlay() {
    print('Starting playback...');
    _player.startPlaying();
    _player.setState(PlayingState(_player));
  }
  
  @override
  void clickStop() {
    print('Already stopped');
  }
  
  @override
  void clickNext() {
    print('Skipping to next track...');
    _player.nextTrack();
  }
  
  @override
  void clickPrevious() {
    print('Going to previous track...');
    _player.previousTrack();
  }
}
