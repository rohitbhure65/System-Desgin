export class ConfigurationMemento {
  private theme: string;
  private fontSize: number;
  private notificationsEnabled: boolean;
  
  constructor(theme: string, fontSize: number, notifications: boolean) {
    this.theme = theme;
    this.fontSize = fontSize;
    this.notificationsEnabled = notifications;
  }
  
  getTheme(): string { return this.theme; }
  getFontSize(): number { return this.fontSize; }
  getNotificationsEnabled(): boolean { return this.notificationsEnabled; }
}

export class ApplicationSettings {
  private theme: string = 'light';
  private fontSize: number = 12;
  private notificationsEnabled: boolean = true;
  
  setTheme(newTheme: string): void {
    this.theme = newTheme;
    console.log(`Theme changed to ${this.theme}`);
  }
  
  setFontSize(size: number): void {
    this.fontSize = size;
    console.log(`Font size set to ${this.fontSize}`);
  }
  
  setNotificationsEnabled(enabled: boolean): void {
    this.notificationsEnabled = enabled;
    console.log(`Notifications ${enabled ? 'enabled' : 'disabled'}`);
  }
  
  displaySettings(): void {
    console.log('=== Current Settings ===');
    console.log(`Theme: ${this.theme}`);
    console.log(`Font Size: ${this.fontSize}`);
    console.log(`Notifications: ${this.notificationsEnabled ? 'Enabled' : 'Disabled'}`);
    console.log('=====================');
  }
  
  saveConfiguration(): ConfigurationMemento {
    return new ConfigurationMemento(this.theme, this.fontSize, this.notificationsEnabled);
  }
  
  restoreConfiguration(memento: ConfigurationMemento): void {
    this.theme = memento.getTheme();
    this.fontSize = memento.getFontSize();
    this.notificationsEnabled = memento.getNotificationsEnabled();
    console.log('Configuration restored!');
    this.displaySettings();
  }
}
