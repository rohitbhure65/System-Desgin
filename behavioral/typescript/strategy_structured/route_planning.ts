import { RouteStrategy } from './interfaces';

export class FastestRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating fastest route from ${from} to ${to}`);
    console.log('  Using highways and main roads to minimize time');
    console.log('  Estimated time: 25 minutes');
  }
}

export class ShortestRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating shortest route from ${from} to ${to}`);
    console.log('  Using direct path to minimize distance');
    console.log('  Estimated distance: 15 km');
  }
}

export class ScenicRoute implements RouteStrategy {
  calculateRoute(from: string, to: string): void {
    console.log(`Calculating scenic route from ${from} to ${to}`);
    console.log('  Using parks and landmarks for best views');
    console.log('  Estimated time: 45 minutes');
  }
}

export class NavigationSystem {
  private strategy: RouteStrategy | null = null;
  
  setRouteStrategy(strategy: RouteStrategy): void {
    this.strategy = strategy;
  }
  
  navigate(from: string, to: string): void {
    console.log('\n=== Navigation ===');
    console.log(`From: ${from}`);
    console.log(`To: ${to}`);
    
    if (this.strategy) {
      this.strategy.calculateRoute(from, to);
    } else {
      console.log('No route strategy selected');
    }
  }
}
