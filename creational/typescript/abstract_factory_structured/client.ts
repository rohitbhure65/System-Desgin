import { GUIFactory, Button, Checkbox } from './interfaces';

export class GUIApplication {
  private button: Button;
  private checkbox: Checkbox;
  
  constructor(factory: GUIFactory) {
    this.button = factory.createButton();
    this.checkbox = factory.createCheckbox();
  }
  
  public renderUI(): void {
    console.log('Rendering UI components...');
    console.log(`Button: ${this.button.getName()}`);
    console.log(`Checkbox: ${this.checkbox.getName()}`);
    
    this.button.render();
    this.checkbox.render();
  }
  
  public interact(): void {
    console.log('\nUser interaction...');
    this.button.click();
    this.checkbox.check();
  }
}
