interface Strategy {
    int execute(int a, int b);
}

class Add implements Strategy {
    public int execute(int a, int b) {
        return a + b;
    }
}

class Subtract implements Strategy {
    public int execute(int a, int b) {
        return a - b;
    }
}

class Context {
    private Strategy strategy;

    public void setStrategy(Strategy strategy) {
        this.strategy = strategy;
    }

    public int executeStrategy(int a, int b) {
        return strategy.execute(a, b);
    }
}

public class strategy {
    public static void main(String[] args) {
        Context context = new Context();
        context.setStrategy(new Add());
        System.out.println("Add: " + context.executeStrategy(3, 4));
    }
}
