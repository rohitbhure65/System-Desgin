import 'interfaces.dart';
import 'adapters.dart';

class AudioPlayer implements MediaPlayer {
  MediaAdapter? _mediaAdapter;
  
  @override
  void play(String audioType, String fileName) {
    if (audioType == 'mp3') {
      print('Playing mp3 file: $fileName');
    } else if (audioType == 'vlc' || audioType == 'mp4') {
      _mediaAdapter = MediaAdapter();
      _mediaAdapter!.play(audioType, fileName);
    } else {
      print('Invalid media. $audioType format not supported');
    }
  }
}
