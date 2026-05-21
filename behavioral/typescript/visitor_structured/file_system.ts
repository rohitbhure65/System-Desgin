import { FileSystemVisitor, FileSystemNode } from './interfaces';

export class File implements FileSystemNode {
  private name: string;
  private size: number;
  
  constructor(name: string, size: number) {
    this.name = name;
    this.size = size;
  }
  
  accept(visitor: FileSystemVisitor): void {
    visitor.visitFile(this);
  }
  
  getName(): string { return this.name; }
  getSize(): number { return this.size; }
}

export class Directory implements FileSystemNode {
  private name: string;
  private children: FileSystemNode[] = [];
  
  constructor(name: string) {
    this.name = name;
  }
  
  addChild(child: FileSystemNode): void {
    this.children.push(child);
  }
  
  accept(visitor: FileSystemVisitor): void {
    visitor.visitDirectory(this);
  }
  
  getName(): string { return this.name; }
  getSize(): number {
    return this.children.reduce((total, child) => total + child.getSize(), 0);
  }
}

export class SizeCalculator implements FileSystemVisitor {
  private totalSize: number = 0;
  
  visitFile(file: any): void {
    this.totalSize += file.getSize();
    console.log(`File: ${file.getName()} - ${file.getSize()} bytes`);
  }
  
  visitDirectory(directory: any): void {
    console.log(`Directory: ${directory.getName()} - ${directory.getSize()} bytes`);
    this.totalSize += directory.getSize();
  }
  
  getTotalSize(): number {
    return this.totalSize;
  }
}

export class XMLExporter implements FileSystemVisitor {
  visitFile(file: any): void {
    console.log(`  <file name="${file.getName()}" size="${file.getSize()}"/>`);
  }
  
  visitDirectory(directory: any): void {
    console.log(`  <directory name="${directory.getName()}" size="${directory.getSize()}">`);
  }
}
