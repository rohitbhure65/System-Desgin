import 'interfaces.dart';

class NumberExpression extends Expression {
  final int _value;
  
  NumberExpression(this._value);
  
  @override
  int interpret() {
    return _value;
  }
}

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
    }
    
    return left;
  }
  
  Expression _parseFactor() {
    _skipWhitespace();
    
    if (_peek() == '(') {
      _next();
      final expr = _parseExpression();
      _next();
      return expr;
    }
    
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
