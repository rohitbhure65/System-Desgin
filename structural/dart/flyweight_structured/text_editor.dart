import 'interfaces.dart';

class ConcreteCharacterFormat extends CharacterFormat {
  @override
  final String font;
  @override
  final int size;
  @override
  final String color;
  final bool bold;
  final bool italic;
  
  ConcreteCharacterFormat(this.font, this.size, this.color, this.bold, this.italic);
  
  @override
  void apply(String text) {
    var output = 'Rendering \'$text\' with font: $font, size: $size, color: $color';
    if (bold) output += ', bold';
    if (italic) output += ', italic';
    print(output);
  }
}

class CharacterFormatFactory {
  final Map<String, CharacterFormat> _formats = {};
  
  String _getKey(String font, int size, String color, bool bold, bool italic) {
    return '$font|$size|$color|${bold ? 'B' : ''}|${italic ? 'I' : ''}';
  }
  
  CharacterFormat getFormat(String font, int size, String color, bool bold, bool italic) {
    var key = _getKey(font, size, color, bold, italic);
    
    if (!_formats.containsKey(key)) {
      print('Creating new format: $font ${size}pt');
      _formats[key] = ConcreteCharacterFormat(font, size, color, bold, italic);
    } else {
      print('Reusing existing format: $font ${size}pt');
    }
    
    return _formats[key]!;
  }
  
  int getTotalFormats() {
    return _formats.length;
  }
}

class Character {
  final String symbol;
  final CharacterFormat format;
  
  Character(this.symbol, this.format);
  
  void render() {
    format.apply(symbol);
  }
}
