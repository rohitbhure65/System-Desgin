export interface Prototype {
  clone(): Prototype;
  display(): void;
  getType(): string;
}
