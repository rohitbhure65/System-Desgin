export interface RemoteServer {
  request(data: string): void;
}

export class RealRemoteServer implements RemoteServer {
  request(data: string): void {
    console.log(`Remote server processing request: ${data}`);
  }
}

export class RemoteServerProxy implements RemoteServer {
  private remoteServer?: RealRemoteServer;
  private serverAddress: string;
  
  constructor(address: string) {
    this.serverAddress = address;
  }
  
  private connectToServer(): void {
    console.log(`Connecting to remote server at ${this.serverAddress}...`);
  }
  
  request(data: string): void {
    if (!this.remoteServer) {
      this.connectToServer();
      this.remoteServer = new RealRemoteServer();
    }
    console.log('Proxy forwarding request to remote server...');
    this.remoteServer.request(data);
  }
}
