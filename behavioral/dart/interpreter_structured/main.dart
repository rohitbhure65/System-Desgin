import 'interfaces.dart';
import 'arithmetic_expressions.dart';
import 'boolean_expressions.dart';
import 'pattern_expressions.dart';

void main() {
  print('=== Interpreter Pattern Demo ===\n');
  
  // Example 1: Arithmetic Expression
  print('--- Arithmetic Expression Example ---');
  
  final expressions = [
    '2 + 3 * 4',
    '10 - 5 + 3',
    '2 * 3 + 4 * 5'
  ];
  
  for (final expr in expressions) {
    print('\nExpression: $expr');
    final parser = ExpressionParser(expr);
    final parsedExpr = parser.parse();
    print('Result: ${parsedExpr.interpret()}');
  }
  
  // Example 2: Boolean Expression
  print('\n--- Boolean Expression Example ---');
  
  final context = Context();
  context.setVariable('A', 1);
  context.setVariable('B', 0);
  context.setVariable('C', 1);
  
  print('\nVariables: A=1, B=0, C=1');
  
  final expr1 = AndExpression(
    VariableExpression('A'),
    OrExpression(
      VariableExpression('B'),
      VariableExpression('C')
    )
  );
  print('\nA AND (B OR C): ${expr1.evaluate(context)}');
  
  final expr2 = NotExpression(
    AndExpression(
      VariableExpression('A'),
      VariableExpression('B')
    )
  );
  print('NOT (A AND B): ${expr2.evaluate(context)}');
  
  // Example 3: Pattern Matching
  print('\n--- Pattern Matching Example ---');
  
  final texts = [
    'Hello World',
    'Design Patterns',
    'Hello Design Patterns',
    'World of Patterns'
  ];
  
  print('\nMatching "Hello":');
  final helloPattern = LiteralPattern('Hello');
  for (final text in texts) {
    print('  "$text": ${helloPattern.match(text) ? 'Match' : 'No match'}');
  }
  
  print('\nMatching "Design*":');
  final designPattern = WildcardPattern('Design*');
  for (final text in texts) {
    print('  "$text": ${designPattern.match(text) ? 'Match' : 'No match'}');
  }
  
  print('\nMatching "Hello" OR "World":');
  final orPattern = OrPattern();
  orPattern.addPattern(LiteralPattern('Hello'));
  orPattern.addPattern(LiteralPattern('World'));
  for (final text in texts) {
    print('  "$text": ${orPattern.match(text) ? 'Match' : 'No match'}');
  }
}
