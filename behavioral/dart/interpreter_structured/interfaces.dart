abstract class Expression {
  int interpret();
}

abstract class BooleanExpression {
  bool evaluate(Context context);
}

abstract class PatternExpression {
  bool match(String text);
}

class Context {
  final Map<String, int> _variables = {};
  
  void setVariable(String name, int value) {
    _variables[name] = value;
  }
  
  int getVariable(String name) {
    return _variables[name] ?? 0;
  }
}
