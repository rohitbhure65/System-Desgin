export interface PaymentStrategy {
  pay(amount: number): void;
}

export interface SortingStrategy {
  sort(data: number[]): void;
}

export interface RouteStrategy {
  calculateRoute(from: string, to: string): void;
}
