import { Expression } from './interfaces';

export class NumberExpression implements Expression {
  private value: number;
  
  constructor(value: number) {
    this.value = value;
  }
  
  interpret(): number {
    return this.value;
  }
}

export class AddExpression implements Expression {
  private left: Expression;
  private right: Expression;
  
  constructor(left: Expression, right: Expression) {
    this.left = left;
    this.right = right;
  }
  
  interpret(): number {
    return this.left.interpret() + this.right.interpret();
  }
}

export class SubtractExpression implements Expression {
  private left: Expression;
  private right: Expression;
  
  constructor(left: Expression, right: Expression) {
    this.left = left;
    this.right = right;
  }
  
  interpret(): number {
    return this.left.interpret() - this.right.interpret();
  }
}

export class MultiplyExpression implements Expression {
  private left: Expression;
  private right: Expression;
  
  constructor(left: Expression, right: Expression) {
    this.left = left;
    this.right = right;
  }
  
  interpret(): number {
    return this.left.interpret() * this.right.interpret();
  }
}

export class ExpressionParser {
  private expression: string;
  private pos: number = 0;
  
  constructor(expr: string) {
    this.expression = expr;
  }
  
  private peek(): string {
    return this.pos < this.expression.length ? this.expression[this.pos] : '\0';
  }
  
  private next(): string {
    return this.expression[this.pos++];
  }
  
  private skipWhitespace(): void {
    while (this.pos < this.expression.length && /\s/.test(this.expression[this.pos])) {
      this.pos++;
    }
  }
  
  private parseExpression(): Expression {
    let left = this.parseTerm();
    
    while (this.peek() === '+' || this.peek() === '-') {
      const op = this.next();
      const right = this.parseTerm();
      
      if (op === '+') {
        left = new AddExpression(left, right);
      } else {
        left = new SubtractExpression(left, right);
      }
    }
    
    return left;
  }
  
  private parseTerm(): Expression {
    let left = this.parseFactor();
    
    while (this.peek() === '*' || this.peek() === '/') {
      const op = this.next();
      const right = this.parseFactor();
      
      if (op === '*') {
        left = new MultiplyExpression(left, right);
      }
    }
    
    return left;
  }
  
  private parseFactor(): Expression {
    this.skipWhitespace();
    
    if (this.peek() === '(') {
      this.next();
      const expr = this.parseExpression();
      this.next();
      return expr;
    }
    
    this.skipWhitespace();
    let value = 0;
    while (this.pos < this.expression.length && /\d/.test(this.expression[this.pos])) {
      value = value * 10 + parseInt(this.expression[this.pos]);
      this.pos++;
    }
    
    return new NumberExpression(value);
  }
  
  parse(): Expression {
    return this.parseExpression();
  }
}
