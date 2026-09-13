package decorator_structured;

interface DataSource {
    void writeData(String data);
}

class FileDataSource implements DataSource {
    public void writeData(String data) {
        System.out.println("Write: " + data);
    }
}
