abstract class RemoteServer {
  void request(String data);
}

class RealRemoteServer extends RemoteServer {
  @override
  void request(String data) {
    print('Remote server processing request: $data');
  }
}

class RemoteServerProxy extends RemoteServer {
  RealRemoteServer? _remoteServer;
  final String serverAddress;
  
  RemoteServerProxy(this.serverAddress);
  
  void _connectToServer() {
    print('Connecting to remote server at $serverAddress...');
  }
  
  @override
  void request(String data) {
    if (_remoteServer == null) {
      _connectToServer();
      _remoteServer = RealRemoteServer();
    }
    print('Proxy forwarding request to remote server...');
    _remoteServer!.request(data);
  }
}
