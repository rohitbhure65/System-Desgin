import 'interfaces.dart';

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
    int patternPos = 0;
    int textPos = 0;
    
    while (patternPos < _pattern.length && textPos < text.length) {
      if (_pattern[patternPos] == '*') {
        patternPos++;
        if (patternPos == _pattern.length) {
          return true;
        }
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
