import 'interfaces.dart';

class GUIApplication {
  final Button _button;
  final Checkbox _checkbox;
  
  GUIApplication(GUIFactory factory)
      : _button = factory.createButton(),
        _checkbox = factory.createCheckbox();
  
  void renderUI() {
    print('Rendering UI components...');
    print('Button: ${_button.name}');
    print('Checkbox: ${_checkbox.name}');
    
    _button.render();
    _checkbox.render();
  }
  
  void interact() {
    print('\nUser interaction...');
    _button.click();
    _checkbox.check();
  }
}
