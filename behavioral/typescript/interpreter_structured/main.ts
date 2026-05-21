import { Context } from './interfaces';
import { ExpressionParser } from './arithmetic_expressions';
import { VariableExpression, ConstantExpression, AndExpression, OrExpression, NotExpression } from './boolean_expressions';
import { LiteralPattern, WildcardPattern, OrPattern } from './pattern_expressions';

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

const expr1 = new AndExpression(
  new VariableExpression('A'),
  new OrExpression(
    new VariableExpression('B'),
    new VariableExpression('C')
  )
);
console.log(`\nA AND (B OR C): ${expr1.evaluate(context)}`);

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
