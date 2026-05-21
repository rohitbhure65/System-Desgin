import { BooleanExpression, Context } from './interfaces';

export class VariableExpression implements BooleanExpression {
  private variableName: string;
  
  constructor(name: string) {
    this.variableName = name;
  }
  
  evaluate(context: Context): boolean {
    return context.getVariable(this.variableName) !== 0;
  }
}

export class ConstantExpression implements BooleanExpression {
  private value: boolean;
  
  constructor(value: boolean) {
    this.value = value;
  }
  
  evaluate(context: Context): boolean {
    return this.value;
  }
}

export class AndExpression implements BooleanExpression {
  private left: BooleanExpression;
  private right: BooleanExpression;
  
  constructor(left: BooleanExpression, right: BooleanExpression) {
    this.left = left;
    this.right = right;
  }
  
  evaluate(context: Context): boolean {
    return this.left.evaluate(context) && this.right.evaluate(context);
  }
}

export class OrExpression implements BooleanExpression {
  private left: BooleanExpression;
  private right: BooleanExpression;
  
  constructor(left: BooleanExpression, right: BooleanExpression) {
    this.left = left;
    this.right = right;
  }
  
  evaluate(context: Context): boolean {
    return this.left.evaluate(context) || this.right.evaluate(context);
  }
}

export class NotExpression implements BooleanExpression {
  private expression: BooleanExpression;
  
  constructor(expr: BooleanExpression) {
    this.expression = expr;
  }
  
  evaluate(context: Context): boolean {
    return !this.expression.evaluate(context);
  }
}
