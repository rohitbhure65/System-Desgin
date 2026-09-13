package decorator_structured;

class EncryptionDecorator implements DataSource {
    private DataSource wrappee;

    public EncryptionDecorator(DataSource source) {
        this.wrappee = source;
    }

    public void writeData(String data) {
        wrappee.writeData("Encrypted(" + data + ")");
    }
}
