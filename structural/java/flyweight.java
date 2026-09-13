import java.util.HashMap;
import java.util.Map;

class TreeType {
    private String name, color;

    public TreeType(String name, String color) {
        this.name = name;
        this.color = color;
    }

    public void draw(int x, int y) {
        System.out.println("Tree " + name + " (" + color + ") at " + x + "," + y);
    }
}

class TreeFactory {
    static Map<String, TreeType> treeTypes = new HashMap<>();

    public static TreeType getTreeType(String name, String color) {
        if (!treeTypes.containsKey(name))
            treeTypes.put(name, new TreeType(name, color));
        return treeTypes.get(name);
    }
}

public class flyweight {
    public static void main(String[] args) {
        TreeType type = TreeFactory.getTreeType("Oak", "Green");
        type.draw(10, 20);
    }
}
