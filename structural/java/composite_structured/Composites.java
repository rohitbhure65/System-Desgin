package composite_structured;

import java.util.ArrayList;
import java.util.List;

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
