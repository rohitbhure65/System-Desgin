interface Subject {
    void request();
}

class RealSubject implements Subject {
    public void request() {
        System.out.println("RealSubject request");
    }
}

class Proxy implements Subject {
    private RealSubject realSubject;

    public void request() {
        if (realSubject == null)
            realSubject = new RealSubject();
        realSubject.request();
    }
}

public class proxy {
    public static void main(String[] args) {
        Subject p = new Proxy();
        p.request();
    }
}
