package composite_structured;

public class Main {
    public static void main(String[] args) {
        CompoundGraphic comp = new CompoundGraphic();
        comp.add(new Dot());
        comp.draw();
    }
}
