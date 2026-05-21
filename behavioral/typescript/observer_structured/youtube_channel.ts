import { Observer, Subject } from './interfaces';

export class YouTubeChannel extends Subject {
  private channelName: string;
  
  constructor(name: string) {
    super();
    this.channelName = name;
  }
  
  uploadVideo(videoTitle: string): void {
    console.log(`\n${this.channelName} uploaded: ${videoTitle}`);
    this.notify(`New video: ${videoTitle}`);
  }
  
  goLive(streamTitle: string): void {
    console.log(`\n${this.channelName} is live: ${streamTitle}`);
    this.notify(`Live stream started: ${streamTitle}`);
  }
}

export class Subscriber implements Observer {
  private name: string;
  
  constructor(name: string) {
    this.name = name;
  }
  
  update(message: string): void {
    console.log(`  ${this.name} received notification: ${message}`);
  }
}

export class NotificationService implements Observer {
  update(message: string): void {
    console.log(`  [NotificationService] Push notification sent: ${message}`);
  }
}
