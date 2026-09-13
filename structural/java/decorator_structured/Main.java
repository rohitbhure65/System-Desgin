package decorator_structured;

public class Main {
    public static void main(String[] args) {
        DataSource d = new EncryptionDecorator(new FileDataSource());
        d.writeData("Hello");
    }
}
