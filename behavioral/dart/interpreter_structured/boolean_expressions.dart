import 'interfaces.dart';

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
