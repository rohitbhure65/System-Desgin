import { MediaPlayer } from './interfaces';
import { MediaAdapter } from './adapters';

export class AudioPlayer implements MediaPlayer {
  private mediaAdapter?: MediaAdapter;
  
  play(audioType: string, fileName: string): void {
    if (audioType === 'mp3') {
      console.log(`Playing mp3 file: ${fileName}`);
    } else if (audioType === 'vlc' || audioType === 'mp4') {
      this.mediaAdapter = new MediaAdapter();
      this.mediaAdapter.play(audioType, fileName);
    } else {
      console.log(`Invalid media. ${audioType} format not supported`);
    }
  }
}
