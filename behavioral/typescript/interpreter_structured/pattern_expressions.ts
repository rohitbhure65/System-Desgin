import { PatternExpression } from './interfaces';

export class LiteralPattern implements PatternExpression {
  private literal: string;
  
  constructor(lit: string) {
    this.literal = lit;
  }
  
  match(text: string): boolean {
    return text.includes(this.literal);
  }
}

export class WildcardPattern implements PatternExpression {
  private pattern: string;
  
  constructor(pat: string) {
    this.pattern = pat;
  }
  
  match(text: string): boolean {
    let patternPos = 0;
    let textPos = 0;
    
    while (patternPos < this.pattern.length && textPos < text.length) {
      if (this.pattern[patternPos] === '*') {
        patternPos++;
        if (patternPos === this.pattern.length) {
          return true;
        }
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

export class OrPattern implements PatternExpression {
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
