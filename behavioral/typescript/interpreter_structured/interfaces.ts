export interface Expression {
  interpret(): number;
}

export interface BooleanExpression {
  evaluate(context: Context): boolean;
}

export interface PatternExpression {
  match(text: string): boolean;
}

export class Context {
  private variables: Map<string, number> = new Map();
  
  setVariable(name: string, value: number): void {
    this.variables.set(name, value);
  }
  
  getVariable(name: string): number {
    return this.variables.get(name) || 0;
  }
}
