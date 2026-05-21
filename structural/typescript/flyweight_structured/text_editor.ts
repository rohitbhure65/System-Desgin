import { CharacterFormat } from './interfaces';

export class ConcreteCharacterFormat implements CharacterFormat {
  constructor(
    private font: string,
    private size: number,
    private color: string,
    private bold: boolean,
    private italic: boolean
  ) {}
  
  apply(text: string): void {
    let output = `Rendering '${text}' with font: ${this.font}, size: ${this.size}, color: ${this.color}`;
    if (this.bold) output += ', bold';
    if (this.italic) output += ', italic';
    console.log(output);
  }
  
  getFont(): string {
    return this.font;
  }
  
  getSize(): number {
    return this.size;
  }
  
  getColor(): string {
    return this.color;
  }
}

export class CharacterFormatFactory {
  private formats: Map<string, CharacterFormat> = new Map();
  
  private getKey(font: string, size: number, color: string, bold: boolean, italic: boolean): string {
    return `${font}|${size}|${color}|${bold ? 'B' : ''}|${italic ? 'I' : ''}`;
  }
  
  getFormat(font: string, size: number, color: string, bold: boolean, italic: boolean): CharacterFormat {
    const key = this.getKey(font, size, color, bold, italic);
    
    if (!this.formats.has(key)) {
      console.log(`Creating new format: ${font} ${size}pt`);
      this.formats.set(key, new ConcreteCharacterFormat(font, size, color, bold, italic));
    } else {
      console.log(`Reusing existing format: ${font} ${size}pt`);
    }
    
    return this.formats.get(key)!;
  }
  
  getTotalFormats(): number {
    return this.formats.size;
  }
}

export class Character {
  constructor(
    private symbol: string,
    private format: CharacterFormat
  ) {}
  
  render(): void {
    this.format.apply(this.symbol);
  }
}
