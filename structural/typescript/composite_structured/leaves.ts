import { FileSystemComponent, Employee, Graphic } from './components';

export class File extends FileSystemComponent {
  private name: string;
  private size: number;
  
  constructor(name: string, size: number) { super(); this.name = name; this.size = size; }
  display(indent: string = ''): void { console.log(`\${indent}File: \${this.name} (\${this.size} bytes)`); }
  getSize(): number { return this.size; }
}

export class Worker extends Employee {
  private name: string;
  private position: string;
  
  constructor(name: string, position: string) { super(); this.name = name; this.position = position; }
  print(indent: string = ''): void { console.log(`\${indent}Employee: \${this.name} - \${this.position}`); }
}

export class Circle extends Graphic {
  private name: string;
  constructor(name: string) { super(); this.name = name; }
  draw(indent: string = ''): void { console.log(`\${indent}Drawing Circle: \${this.name}`); }
}

export class Square extends Graphic {
  private name: string;
  constructor(name: string) { super(); this.name = name; }
  draw(indent: string = ''): void { console.log(`\${indent}Drawing Square: \${this.name}`); }
}
