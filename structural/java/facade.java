class VideoFile {
}

class CodecFactory {
}

class BitrateReader {
}

class AudioMixer {
}

class VideoConverter {
    public void convertVideo(String fileName, String format) {
        System.out.println("Converting " + fileName);
    }
}

public class facade {
    public static void main(String[] args) {
        VideoConverter converter = new VideoConverter();
        converter.convertVideo("file.mp4", "ogg");
    }
}
