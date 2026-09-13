package facade_structured;

public class Main {
    public static void main(String[] args) {
        VideoConverter converter = new VideoConverter();
        converter.convertVideo("file.mp4", "ogg");
    }
}
