interface Target {
    void request();
}

class Adaptee {
    public void specificRequest() {
        System.out.println("Specific request");
    }
}

class Adapter implements Target {
    private Adaptee adaptee = new Adaptee();

    public void request() {
        adaptee.specificRequest();
    }
}

public class adapter {
    public static void main(String[] args) {
        Target target = new Adapter();
        target.request();
    }
}
