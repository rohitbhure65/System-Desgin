package adapter_structured;

class Adapter implements Target {
    private Adaptee adaptee = new Adaptee();

    public void request() {
        adaptee.specificRequest();
    }
}
