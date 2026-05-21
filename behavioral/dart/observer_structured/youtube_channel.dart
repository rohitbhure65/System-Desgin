import 'interfaces.dart';

class YouTubeChannel extends Subject {
  final String _channelName;
  
  YouTubeChannel(this._channelName);
  
  void uploadVideo(String videoTitle) {
    print('\n$_channelName uploaded: $videoTitle');
    notify('New video: $videoTitle');
  }
  
  void goLive(String streamTitle) {
    print('\n$_channelName is live: $streamTitle');
    notify('Live stream started: $streamTitle');
  }
}

class Subscriber implements Observer {
  final String _name;
  
  Subscriber(this._name);
  
  @override
  void update(String message) {
    print('  $_name received notification: $message');
  }
}

class NotificationService implements Observer {
  @override
  void update(String message) {
    print('  [NotificationService] Push notification sent: $message');
  }
}
