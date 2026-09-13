package prototype_structured;

class Shape implements Prototype {
    public int x, y;
    public String color;
    public Shape() {}
    public Shape(Shape target) {
        if (target != null) { this.x = target.x; this.y = target.y; this.color = target.color; }
    }
    public Prototype clone() { return new Shape(this); }
}
