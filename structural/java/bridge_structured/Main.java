package bridge_structured;

public class Main {
    public static void main(String[] args) {
        Remote remote = new Remote(new TV());
        remote.togglePower();
    }
}
