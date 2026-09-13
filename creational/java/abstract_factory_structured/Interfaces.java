
interface Button {
    void render();
}

interface Checkbox {
    void render();
}

interface GUIFactory {
    Button createButton();

    Checkbox createCheckbox();
}
