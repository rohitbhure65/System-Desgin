export interface Visitor {
  visitBook(book: any): void;
  visitFruit(fruit: any): void;
  visitElectronic(electronic: any): void;
}

export interface Item {
  accept(visitor: Visitor): void;
  getPrice(): number;
}

export interface FileSystemVisitor {
  visitFile(file: any): void;
  visitDirectory(directory: any): void;
}

export interface FileSystemNode {
  accept(visitor: FileSystemVisitor): void;
  getName(): string;
  getSize(): number;
}

export interface SalaryVisitor {
  visitEmployee(employee: any): void;
  visitManager(manager: any): void;
  visitDeveloper(developer: any): void;
  visitDesigner(designer: any): void;
}

export interface Employee {
  accept(visitor: SalaryVisitor): void;
  getName(): string;
  getBaseSalary(): number;
}
