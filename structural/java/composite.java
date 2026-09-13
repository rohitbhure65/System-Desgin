import java.util.ArrayList;
import java.util.List;

interface Graphic {
    void draw();
}

class Dot implements Graphic {
    public void draw() {
        System.out.println("Dot");
    }
}

class CompoundGraphic implements Graphic {
    private List<Graphic> children = new ArrayList<>();

    public void add(Graphic g) {
        children.add(g);
    }

    public void draw() {
        for (Graphic g : children)
            g.draw();
    }
}

public class composite {
    public static void main(String[] args) {
        CompoundGraphic comp = new CompoundGraphic();
        comp.add(new Dot());
        comp.draw();
    }
}
