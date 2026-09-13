package prototype_structured;

public class Main {
    public static void main(String[] args) {
        Shape circle = new Shape();
        circle.x = 10;
        circle.y = 20;
        circle.color = "Red";

        Shape clonedCircle = (Shape) circle.clone();
        System.out.println("Cloned Circle Color: " + clonedCircle.color);
    }
}
