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
abstract class Expression {
  int interpret();
}

// Terminal Expression - implements interpret for terminal symbols
class NumberExpression extends Expression {
  final int _value;
  
  NumberExpression(this._value);
  
  @override
  int interpret() {
    return _value;
  }
}

// Non-terminal Expression - implements interpret for operators
class AddExpression extends Expression {
  final Expression _left;
  final Expression _right;
  
  AddExpression(this._left, this._right);
  
  @override
  int interpret() {
    return _left.interpret() + _right.interpret();
  }
}

class SubtractExpression extends Expression {
  final Expression _left;
  final Expression _right;
  
  SubtractExpression(this._left, this._right);
  
  @override
  int interpret() {
    return _left.interpret() - _right.interpret();
  }
}

class MultiplyExpression extends Expression {
  final Expression _left;
  final Expression _right;
  
  MultiplyExpression(this._left, this._right);
  
  @override
  int interpret() {
    return _left.interpret() * _right.interpret();
  }
}

// Parser - parses the expression and builds the syntax tree
class ExpressionParser {
  final String _expression;
  int _pos = 0;
  
  ExpressionParser(this._expression);
  
  String _peek() {
    return _pos < _expression.length ? _expression[_pos] : '\0';
  }
  
  String _next() {
    return _expression[_pos++];
  }
  
  void _skipWhitespace() {
    while (_pos < _expression.length && RegExp(r'\s').hasMatch(_expression[_pos])) {
      _pos++;
    }
  }
  
  Expression _parseExpression() {
    var left = _parseTerm();
    
    while (_peek() == '+' || _peek() == '-') {
      final op = _next();
      final right = _parseTerm();
      
      if (op == '+') {
        left = AddExpression(left, right);
      } else {
        left = SubtractExpression(left, right);
      }
    }
    
    return left;
  }
  
  Expression _parseTerm() {
    var left = _parseFactor();
    
    while (_peek() == '*' || _peek() == '/') {
      final op = _next();
      final right = _parseFactor();
      
      if (op == '*') {
        left = MultiplyExpression(left, right);
      }
      // Division not implemented for simplicity
    }
    
    return left;
  }
  
  Expression _parseFactor() {
    _skipWhitespace();
    
    if (_peek() == '(') {
      _next();  // consume '('
      final expr = _parseExpression();
      _next();  // consume ')'
      return expr;
    }
    
    // Parse number
    _skipWhitespace();
    var value = 0;
    while (_pos < _expression.length && RegExp(r'\d').hasMatch(_expression[_pos])) {
      value = value * 10 + int.parse(_expression[_pos]);
      _pos++;
    }
    
    return NumberExpression(value);
  }
  
  Expression parse() {
    return _parseExpression();
  }
}

// Context - provides information to the interpreter
class Context {
  final Map<String, int> _variables = {};
  
  void setVariable(String name, int value) {
    _variables[name] = value;
  }
  
  int getVariable(String name) {
    return _variables[name] ?? 0;
  }
}

// Example 2: Boolean Expression Interpreter
// Shows how Interpreter can be used for boolean logic

abstract class BooleanExpression {
  bool evaluate(Context context);
}

class VariableExpression implements BooleanExpression {
  final String _variableName;
  
  VariableExpression(this._variableName);
  
  @override
  bool evaluate(Context context) {
    return context.getVariable(_variableName) != 0;
  }
}

class ConstantExpression implements BooleanExpression {
  final bool _value;
  
  ConstantExpression(this._value);
  
  @override
  bool evaluate(Context context) {
    return _value;
  }
}

class AndExpression implements BooleanExpression {
  final BooleanExpression _left;
  final BooleanExpression _right;
  
  AndExpression(this._left, this._right);
  
  @override
  bool evaluate(Context context) {
    return _left.evaluate(context) && _right.evaluate(context);
  }
}

class OrExpression implements BooleanExpression {
  final BooleanExpression _left;
  final BooleanExpression _right;
  
  OrExpression(this._left, this._right);
  
  @override
  bool evaluate(Context context) {
    return _left.evaluate(context) || _right.evaluate(context);
  }
}

class NotExpression implements BooleanExpression {
  final BooleanExpression _expression;
  
  NotExpression(this._expression);
  
  @override
  bool evaluate(Context context) {
    return !_expression.evaluate(context);
  }
}

// Example 3: String Pattern Matcher
// Shows how Interpreter can be used for pattern matching

abstract class PatternExpression {
  bool match(String text);
}

class LiteralPattern implements PatternExpression {
  final String _literal;
  
  LiteralPattern(this._literal);
  
  @override
  bool match(String text) {
    return text.contains(_literal);
  }
}

class WildcardPattern implements PatternExpression {
  final String _pattern;
  
  WildcardPattern(this._pattern);
  
  @override
  bool match(String text) {
    // Simple wildcard matching: * matches any sequence
    int patternPos = 0;
    int textPos = 0;
    
    while (patternPos < _pattern.length && textPos < text.length) {
      if (_pattern[patternPos] == '*') {
        // Skip wildcard
        patternPos++;
        if (patternPos == _pattern.length) {
          return true;  // Wildcard at end matches rest
        }
        // Find next character in pattern after wildcard
        final nextChar = _pattern[patternPos];
        while (textPos < text.length && text[textPos] != nextChar) {
          textPos++;
        }
      } else if (_pattern[patternPos] == text[textPos]) {
        patternPos++;
        textPos++;
      } else {
        return false;
      }
    }
    
    return patternPos == _pattern.length;
  }
}

class OrPattern implements PatternExpression {
  final List<PatternExpression> _patterns = [];
  
  void addPattern(PatternExpression pattern) {
    _patterns.add(pattern);
  }
  
  @override
  bool match(String text) {
    for (final pattern in _patterns) {
      if (pattern.match(text)) {
        return true;
      }
    }
    return false;
  }
}

// Demo code
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
  
  // A AND (B OR C)
  final expr1 = AndExpression(
    VariableExpression('A'),
    OrExpression(
      VariableExpression('B'),
      VariableExpression('C')
    )
  );
  print('\nA AND (B OR C): ${expr1.evaluate(context)}');
  
  // NOT (A AND B)
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
