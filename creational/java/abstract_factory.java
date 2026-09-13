public class abstract_factory {
    interface Button { void render(); }
    interface Checkbox { void render(); }

    static class WinButton implements Button { public void render() { System.out.println("Windows Button"); } }
    static class MacButton implements Button { public void render() { System.out.println("Mac Button"); } }

    static class WinCheckbox implements Checkbox { public void render() { System.out.println("Windows Checkbox"); } }
    static class MacCheckbox implements Checkbox { public void render() { System.out.println("Mac Checkbox"); } }

    interface GUIFactory {
        Button createButton();
        Checkbox createCheckbox();
    }

    static class WinFactory implements GUIFactory {
        public Button createButton() { return new WinButton(); }
        public Checkbox createCheckbox() { return new WinCheckbox(); }
    }

    static class MacFactory implements GUIFactory {
        public Button createButton() { return new MacButton(); }
        public Checkbox createCheckbox() { return new MacCheckbox(); }
    }

    public static void main(String[] args) {
        GUIFactory factory;
        String os = "win";
        if (os.equals("win"))
            factory = new WinFactory();
        else
            factory = new MacFactory();

        Button button = factory.createButton();
        Checkbox checkbox = factory.createCheckbox();
        button.render();
        checkbox.render();
    }
}
