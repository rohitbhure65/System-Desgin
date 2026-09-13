interface DataSource {
    void writeData(String data);
}

class FileDataSource implements DataSource {
    public void writeData(String data) {
        System.out.println("Write: " + data);
    }
}

class EncryptionDecorator implements DataSource {
    private DataSource wrappee;

    public EncryptionDecorator(DataSource source) {
        this.wrappee = source;
    }

    public void writeData(String data) {
        wrappee.writeData("Encrypted(" + data + ")");
    }
}

public class decorator {
    public static void main(String[] args) {
        DataSource d = new EncryptionDecorator(new FileDataSource());
        d.writeData("Hello");
    }
}
