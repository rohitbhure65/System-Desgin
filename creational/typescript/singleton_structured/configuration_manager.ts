export class ConfigurationManager {
  private static instance: ConfigurationManager | null = null;
  private config: Map<string, string> = new Map();
  
  private constructor(initialConfig?: Record<string, string>) {
    console.log('ConfigurationManager: Initializing...');
    if (initialConfig) {
      Object.entries(initialConfig).forEach(([key, value]) => {
        this.config.set(key, value);
      });
    }
  }
  
  public static getInstance(initialConfig?: Record<string, string>): ConfigurationManager {
    if (!ConfigurationManager.instance) {
      ConfigurationManager.instance = new ConfigurationManager(initialConfig);
    }
    return ConfigurationManager.instance;
  }
  
  public set(key: string, value: string): void { this.config.set(key, value); }
  public get(key: string): string | undefined { return this.config.get(key); }
  
  public displayConfig(): void {
    console.log('Current Configuration:');
    this.config.forEach((value, key) => {
      console.log(`  ${key}: ${value}`);
    });
  }
}
