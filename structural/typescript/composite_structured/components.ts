export abstract class FileSystemComponent {
  abstract display(indent?: string): void;
  abstract getSize(): number;
  
  add(component: FileSystemComponent): void { console.log('Cannot add to a file'); }
  remove(component: FileSystemComponent): void { console.log('Cannot remove from a file'); }
  getChild(index: number): FileSystemComponent | null { return null; }
}

export abstract class Employee {
  abstract print(indent?: string): void;
  add(employee: Employee): void { console.log('Cannot add to a regular employee'); }
  remove(employee: Employee): void { console.log('Cannot remove from a regular employee'); }
}

export abstract class Graphic {
  abstract draw(indent?: string): void;
}
