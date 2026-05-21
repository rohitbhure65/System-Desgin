import { AudioPlayerState } from './interfaces';

export class AudioPlayer {
  private currentState: AudioPlayerState;
  private isPlaying: boolean = false;
  private currentTrack: number = 1;
  private totalTracks: number;
  
  constructor(tracks: number) {
    this.totalTracks = tracks;
    this.currentState = new StoppedState(this);
  }
  
  setState(state: AudioPlayerState): void {
    this.currentState = state;
  }
  
  clickPlay(): void {
    this.currentState.clickPlay();
  }
  
  clickStop(): void {
    this.currentState.clickStop();
  }
  
  clickNext(): void {
    this.currentState.clickNext();
  }
  
  clickPrevious(): void {
    this.currentState.clickPrevious();
  }
  
  startPlaying(): void {
    this.isPlaying = true;
    console.log(`Started playing track ${this.currentTrack}`);
  }
  
  stopPlaying(): void {
    this.isPlaying = false;
    console.log('Stopped playing');
  }
  
  nextTrack(): void {
    this.currentTrack = (this.currentTrack % this.totalTracks) + 1;
    console.log(`Moved to track ${this.currentTrack}`);
  }
  
  previousTrack(): void {
    this.currentTrack = this.currentTrack === 1 ? this.totalTracks : this.currentTrack - 1;
    console.log(`Moved to track ${this.currentTrack}`);
  }
  
  getIsPlaying(): boolean {
    return this.isPlaying;
  }
}

export class PlayingState implements AudioPlayerState {
  private player: AudioPlayer;
  
  constructor(player: AudioPlayer) {
    this.player = player;
  }
  
  clickPlay(): void {
    console.log('Already playing');
  }
  
  clickStop(): void {
    console.log('Stopping playback...');
    this.player.stopPlaying();
    this.player.setState(new StoppedState(this.player));
  }
  
  clickNext(): void {
    console.log('Skipping to next track...');
    this.player.nextTrack();
  }
  
  clickPrevious(): void {
    console.log('Going to previous track...');
    this.player.previousTrack();
  }
}

export class StoppedState implements AudioPlayerState {
  private player: AudioPlayer;
  
  constructor(player: AudioPlayer) {
    this.player = player;
  }
  
  clickPlay(): void {
    console.log('Starting playback...');
    this.player.startPlaying();
    this.player.setState(new PlayingState(this.player));
  }
  
  clickStop(): void {
    console.log('Already stopped');
  }
  
  clickNext(): void {
    console.log('Skipping to next track...');
    this.player.nextTrack();
  }
  
  clickPrevious(): void {
    console.log('Going to previous track...');
    this.player.previousTrack();
  }
}
