abstract class Video {
  void play();
}

class RealVideo extends Video {
  final String filename;
  
  RealVideo(this.filename) {
    _loadVideo();
  }
  
  void _loadVideo() {
    print('Loading video $filename from server...');
  }
  
  @override
  void play() {
    print('Playing video: $filename');
  }
}

class VideoProxy extends Video {
  final String filename;
  RealVideo? _realVideo;
  bool _isLoaded = false;
  
  VideoProxy(this.filename);
  
  @override
  void play() {
    if (!_isLoaded) {
      print('Loading video on first play...');
      _realVideo = RealVideo(filename);
      _isLoaded = true;
    } else {
      print('Using cached video...');
    }
    _realVideo!.play();
  }
}
