package state_structured;

public class Main {
    public static void main(String[] args) {
        Context context = new Context();
        State start = new StartState();
        start.doAction(context);
    }
}
