
class WinButton implements Button {
    public void render() {
        System.out.println("Windows Button");
    }
}

class MacButton implements Button {
    public void render() {
        System.out.println("Mac Button");
    }
}

class WinCheckbox implements Checkbox {
    public void render() {
        System.out.println("Windows Checkbox");
    }
}

class MacCheckbox implements Checkbox {
    public void render() {
        System.out.println("Mac Checkbox");
    }
}
