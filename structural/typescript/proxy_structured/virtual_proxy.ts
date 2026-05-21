// Subject Interface - defines the common interface for RealSubject and Proxy
export interface Image {
  display(): void;
}

// RealSubject - the actual object that the proxy represents
export class RealImage implements Image {
  private filename: string;
  
  constructor(filename: string) {
    this.filename = filename;
    this.loadFromDisk();
  }
  
  private loadFromDisk(): void {
    console.log(`Loading ${this.filename} from disk...`);
  }
  
  display(): void {
    console.log(`Displaying ${this.filename}`);
  }
}

// Proxy - controls access to the RealSubject
export class ProxyImage implements Image {
  private filename: string;
  private realImage?: RealImage;
  
  constructor(filename: string) {
    this.filename = filename;
  }
  
  display(): void {
    if (!this.realImage) {
      console.log('Creating real image on first access...');
      this.realImage = new RealImage(this.filename);
    }
    this.realImage.display();
  }
}
