import { FileSystemComponent, Employee, Graphic } from './components';

export class Directory extends FileSystemComponent {
  private name: string;
  private children: FileSystemComponent[] = [];
  
  constructor(name: string) { super(); this.name = name; }
  
  add(component: FileSystemComponent): void { this.children.push(component); }
  remove(component: FileSystemComponent): void {
    const index = this.children.indexOf(component);
    if (index > -1) { this.children.splice(index, 1); }
  }
  getChild(index: number): FileSystemComponent | null {
    if (index >= 0 && index < this.children.length) { return this.children[index]; }
    return null;
  }
  display(indent: string = ''): void {
    console.log(`\${indent}Directory: \${this.name} (\${this.getSize()} bytes)`);
    for (const child of this.children) { child.display(indent + '  '); }
  }
  getSize(): number {
    let totalSize = 0;
    for (const child of this.children) { totalSize += child.getSize(); }
    return totalSize;
  }
}

export class Manager extends Employee {
  private name: string;
  private title: string;
  private subordinates: Employee[] = [];
  
  constructor(name: string, title: string) { super(); this.name = name; this.title = title; }
  
  add(employee: Employee): void { this.subordinates.push(employee); }
  remove(employee: Employee): void {
    const index = this.subordinates.indexOf(employee);
    if (index > -1) { this.subordinates.splice(index, 1); }
  }
  print(indent: string = ''): void {
    console.log(`\${indent}Manager: \${this.name} - \${this.title}`);
    for (const subordinate of this.subordinates) { subordinate.print(indent + '  '); }
  }
}

export class GraphicGroup extends Graphic {
  private name: string;
  private graphics: Graphic[] = [];
  
  constructor(name: string) { super(); this.name = name; }
  
  add(graphic: Graphic): void { this.graphics.push(graphic); }
  remove(graphic: Graphic): void {
    const index = this.graphics.indexOf(graphic);
    if (index > -1) { this.graphics.splice(index, 1); }
  }
  draw(indent: string = ''): void {
    console.log(`\${indent}Group: \${this.name}`);
    for (const graphic of this.graphics) { graphic.draw(indent + '  '); }
  }
}
