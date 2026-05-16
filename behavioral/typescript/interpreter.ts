/*
 * INTERPRETER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Interpreter pattern defines a grammar for a language and interprets sentences in that language.
 * It's used to evaluate sentences in a language and can be extended with new grammar rules.
 * 
 * WHY DOES IT EXIST?
 * - When you need to interpret a language or expression
 * - When you want to parse and evaluate expressions according to a grammar
 * - When you have a simple grammar that can be represented as a tree structure
 * 
 * WHEN TO USE IT?
 * - When the grammar of the language is relatively simple
 * - When efficiency is not a critical concern
 * - When you want to parse and evaluate expressions dynamically
 * - Common use cases: SQL parsers, regular expression engines, formula evaluators, configuration file parsers
 * 
 * PROS:
 * - Can easily change and extend the grammar
 * - Separates grammar from the interpretation logic
 * - Can be combined with Composite pattern to build parse trees
 * - Makes adding new expressions easy
 * 
 * CONS:
 * - Can become complex for large grammars
 * - Can be less efficient than other parsing approaches
 * - Can lead to many small classes
 * - May be overkill for simple expressions
 * 
 * REAL-WORLD ANALOGY:
 * Think of a calculator. When you type "2 + 3 * 4", the calculator (interpreter) parses the expression according to arithmetic grammar rules. It interprets the multiplication first (operator precedence), then addition, and returns the result. The calculator doesn't need to know the specific numbers in advance - it interprets any valid expression.
 */

// Expression interface - declares the interpret method
interface Expression {
  interpret(): number;
}

// Terminal Expression - implements interpret for terminal symbols
class NumberExpression implements Expression {
  private value: number;
  
  constructor(value: number) {
    this.value = value;
  }
  
  interpret(): number {
    return this.value;
  }
}

// Non-terminal Expression - implements interpret for operators
class AddExpression implements Expression {
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

class SubtractExpression implements Expression {
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

class MultiplyExpression implements Expression {
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

// Parser - parses the expression and builds the syntax tree
class ExpressionParser {
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
      // Division not implemented for simplicity
    }
    
    return left;
  }
  
  private parseFactor(): Expression {
    this.skipWhitespace();
    
    if (this.peek() === '(') {
      this.next();  // consume '('
      const expr = this.parseExpression();
      this.next();  // consume ')'
      return expr;
    }
    
    // Parse number
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

// Context - provides information to the interpreter
class Context {
  private variables: Map<string, number> = new Map();
  
  setVariable(name: string, value: number): void {
    this.variables.set(name, value);
  }
  
  getVariable(name: string): number {
    return this.variables.get(name) || 0;
  }
}

// Example 2: Boolean Expression Interpreter
// Shows how Interpreter can be used for boolean logic

interface BooleanExpression {
  evaluate(context: Context): boolean;
}

class VariableExpression implements BooleanExpression {
  private variableName: string;
  
  constructor(name: string) {
    this.variableName = name;
  }
  
  evaluate(context: Context): boolean {
    return context.getVariable(this.variableName) !== 0;
  }
}

class ConstantExpression implements BooleanExpression {
  private value: boolean;
  
  constructor(value: boolean) {
    this.value = value;
  }
  
  evaluate(context: Context): boolean {
    return this.value;
  }
}

class AndExpression implements BooleanExpression {
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

class OrExpression implements BooleanExpression {
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

class NotExpression implements BooleanExpression {
  private expression: BooleanExpression;
  
  constructor(expr: BooleanExpression) {
    this.expression = expr;
  }
  
  evaluate(context: Context): boolean {
    return !this.expression.evaluate(context);
  }
}

// Example 3: String Pattern Matcher
// Shows how Interpreter can be used for pattern matching

interface PatternExpression {
  match(text: string): boolean;
}

class LiteralPattern implements PatternExpression {
  private literal: string;
  
  constructor(lit: string) {
    this.literal = lit;
  }
  
  match(text: string): boolean {
    return text.includes(this.literal);
  }
}

class WildcardPattern implements PatternExpression {
  private pattern: string;
  
  constructor(pat: string) {
    this.pattern = pat;
  }
  
  match(text: string): boolean {
    // Simple wildcard matching: * matches any sequence
    let patternPos = 0;
    let textPos = 0;
    
    while (patternPos < this.pattern.length && textPos < text.length) {
      if (this.pattern[patternPos] === '*') {
        // Skip wildcard
        patternPos++;
        if (patternPos === this.pattern.length) {
          return true;  // Wildcard at end matches rest
        }
        // Find next character in pattern after wildcard
        const nextChar = this.pattern[patternPos];
        while (textPos < text.length && text[textPos] !== nextChar) {
          textPos++;
        }
      } else if (this.pattern[patternPos] === text[textPos]) {
        patternPos++;
        textPos++;
      } else {
        return false;
      }
    }
    
    return patternPos === this.pattern.length;
  }
}

class OrPattern implements PatternExpression {
  private patterns: PatternExpression[] = [];
  
  addPattern(pattern: PatternExpression): void {
    this.patterns.push(pattern);
  }
  
  match(text: string): boolean {
    for (const pattern of this.patterns) {
      if (pattern.match(text)) {
        return true;
      }
    }
    return false;
  }
}

// Demo code
console.log('=== Interpreter Pattern Demo ===\n');

// Example 1: Arithmetic Expression
console.log('--- Arithmetic Expression Example ---');

const expressions = [
  '2 + 3 * 4',
  '10 - 5 + 3',
  '2 * 3 + 4 * 5'
];

for (const expr of expressions) {
  console.log(`\nExpression: ${expr}`);
  const parser = new ExpressionParser(expr);
  const parsedExpr = parser.parse();
  console.log(`Result: ${parsedExpr.interpret()}`);
}

// Example 2: Boolean Expression
console.log('\n--- Boolean Expression Example ---');

const context = new Context();
context.setVariable('A', 1);
context.setVariable('B', 0);
context.setVariable('C', 1);

console.log('\nVariables: A=1, B=0, C=1');

// A AND (B OR C)
const expr1 = new AndExpression(
  new VariableExpression('A'),
  new OrExpression(
    new VariableExpression('B'),
    new VariableExpression('C')
  )
);
console.log(`\nA AND (B OR C): ${expr1.evaluate(context)}`);

// NOT (A AND B)
const expr2 = new NotExpression(
  new AndExpression(
    new VariableExpression('A'),
    new VariableExpression('B')
  )
);
console.log(`NOT (A AND B): ${expr2.evaluate(context)}`);

// Example 3: Pattern Matching
console.log('\n--- Pattern Matching Example ---');

const texts = [
  'Hello World',
  'Design Patterns',
  'Hello Design Patterns',
  'World of Patterns'
];

console.log('\nMatching "Hello":');
const helloPattern = new LiteralPattern('Hello');
for (const text of texts) {
  console.log(`  "${text}": ${helloPattern.match(text) ? 'Match' : 'No match'}`);
}

console.log('\nMatching "Design*":');
const designPattern = new WildcardPattern('Design*');
for (const text of texts) {
  console.log(`  "${text}": ${designPattern.match(text) ? 'Match' : 'No match'}`);
}

console.log('\nMatching "Hello" OR "World":');
const orPattern = new OrPattern();
orPattern.addPattern(new LiteralPattern('Hello'));
orPattern.addPattern(new LiteralPattern('World'));
for (const text of texts) {
  console.log(`  "${text}": ${orPattern.match(text) ? 'Match' : 'No match'}`);
}
