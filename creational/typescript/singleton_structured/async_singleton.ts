export class AsyncSingleton {
  private static instance: AsyncSingleton | null = null;
  private static isInitializing: boolean = false;
  
  private constructor() {
    console.log('AsyncSingleton: Instance created');
  }

  public static async getInstance(): Promise<AsyncSingleton> {
    if (AsyncSingleton.instance) return AsyncSingleton.instance;

    while (AsyncSingleton.isInitializing) {
      await new Promise(resolve => setTimeout(resolve, 10));
      if (AsyncSingleton.instance) return AsyncSingleton.instance;
    }

    AsyncSingleton.isInitializing = true;
    try {
      console.log('AsyncSingleton: Starting heavy async initialization...');
      await new Promise(resolve => setTimeout(resolve, 100));
      AsyncSingleton.instance = new AsyncSingleton();
    } finally {
      AsyncSingleton.isInitializing = false;
    }

    return AsyncSingleton.instance;
  }
}
