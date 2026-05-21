import { Prototype } from './interfaces';

export class PrototypeRegistry {
  private prototypes: Map<string, Prototype> = new Map();
  
  registerPrototype(key: string, prototype: Prototype): void {
    this.prototypes.set(key, prototype);
  }
  
  clone(key: string): Prototype | null {
    const prototype = this.prototypes.get(key);
    return prototype ? prototype.clone() : null;
  }
}
