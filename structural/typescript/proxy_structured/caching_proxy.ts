export interface Video {
  play(): void;
}

export class RealVideo implements Video {
  private filename: string;
  
  constructor(filename: string) {
    this.filename = filename;
    this.loadVideo();
  }
  
  private loadVideo(): void {
    console.log(`Loading video ${this.filename} from server...`);
  }
  
  play(): void {
    console.log(`Playing video: ${this.filename}`);
  }
}

export class VideoProxy implements Video {
  private filename: string;
  private realVideo?: RealVideo;
  private isLoaded: boolean = false;
  
  constructor(filename: string) {
    this.filename = filename;
  }
  
  play(): void {
    if (!this.isLoaded) {
      console.log('Loading video on first play...');
      this.realVideo = new RealVideo(this.filename);
      this.isLoaded = true;
    } else {
      console.log('Using cached video...');
    }
    this.realVideo!.play();
  }
}
