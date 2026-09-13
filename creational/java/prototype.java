interface Prototype {
    Prototype clone();
}

class Shape implements Prototype {
    public int x, y;
    public String color;

    public Shape() {
    }

    public Shape(Shape target) {
        if (target != null) {
            this.x = target.x;
            this.y = target.y;
            this.color = target.color;
        }
    }

    public Prototype clone() {
        return new Shape(this);
    }
}

public class prototype {
    public static void main(String[] args) {
        Shape circle = new Shape();
        circle.x = 10;
        circle.y = 20;
        circle.color = "Red";

        Shape clonedCircle = (Shape) circle.clone();
        System.out.println("Cloned Circle Color: " + clonedCircle.color);
    }
}
