export class TextEditorMemento {
  private content: string;
  private timestamp: string;
  
  constructor(content: string) {
    this.content = content;
    this.timestamp = this.getCurrentTime();
  }
  
  getContent(): string {
    return this.content;
  }
  
  getTimestamp(): string {
    return this.timestamp;
  }
  
  private getCurrentTime(): string {
    return new Date().toLocaleString();
  }
}

export class TextEditor {
  private content: string = '';
  
  write(text: string): void {
    this.content += text;
    console.log(`Text: "${text}" added`);
  }
  
  setContent(newContent: string): void {
    this.content = newContent;
  }
  
  getContent(): string {
    return this.content;
  }
  
  save(): TextEditorMemento {
    console.log('Saving current state...');
    return new TextEditorMemento(this.content);
  }
  
  restore(memento: TextEditorMemento): void {
    this.content = memento.getContent();
    console.log(`Restored state from ${memento.getTimestamp()}`);
    console.log(`Current content: "${this.content}"`);
  }
}

export class History {
  private mementos: TextEditorMemento[] = [];
  
  push(memento: TextEditorMemento): void {
    this.mementos.push(memento);
  }
  
  pop(): TextEditorMemento | null {
    if (this.mementos.length === 0) {
      return null;
    }
    return this.mementos.pop()!;
  }
  
  size(): number {
    return this.mementos.length;
  }
}
