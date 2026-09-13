package strategy_structured;

public class Main {
    public static void main(String[] args) {
        Context context = new Context();
        context.setStrategy(new Add());
        System.out.println("Add: " + context.executeStrategy(3, 4));
    }
}
