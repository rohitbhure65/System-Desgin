import { Visitor, Item } from './interfaces';

export class Book implements Item {
  private title: string;
  private author: string;
  private price: number;
  
  constructor(title: string, author: string, price: number) {
    this.title = title;
    this.author = author;
    this.price = price;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitBook(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getTitle(): string { return this.title; }
  getAuthor(): string { return this.author; }
}

export class Fruit implements Item {
  private name: string;
  private price: number;
  private weight: number;
  
  constructor(name: string, price: number, weight: number) {
    this.name = name;
    this.price = price;
    this.weight = weight;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitFruit(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getName(): string { return this.name; }
  getWeight(): number { return this.weight; }
}

export class Electronic implements Item {
  private model: string;
  private brand: string;
  private price: number;
  
  constructor(brand: string, model: string, price: number) {
    this.brand = brand;
    this.model = model;
    this.price = price;
  }
  
  accept(visitor: Visitor): void {
    visitor.visitElectronic(this);
  }
  
  getPrice(): number {
    return this.price;
  }
  
  getModel(): string { return this.model; }
  getBrand(): string { return this.brand; }
}

export class PriceCalculator implements Visitor {
  private totalPrice: number = 0;
  
  visitBook(book: any): void {
    this.totalPrice += book.getPrice();
    console.log(`Book: ${book.getTitle()} - $${book.getPrice()}`);
  }
  
  visitFruit(fruit: any): void {
    this.totalPrice += fruit.getPrice();
    console.log(`Fruit: ${fruit.getName()} - $${fruit.getPrice()}`);
  }
  
  visitElectronic(electronic: any): void {
    this.totalPrice += electronic.getPrice();
    console.log(`Electronic: ${electronic.getBrand()} ${electronic.getModel()} - $${electronic.getPrice()}`);
  }
  
  getTotalPrice(): number {
    return this.totalPrice;
  }
}

export class DescriptionGenerator implements Visitor {
  visitBook(book: any): void {
    console.log(`Book: "${book.getTitle()}" by ${book.getAuthor()} - A great read!`);
  }
  
  visitFruit(fruit: any): void {
    console.log(`Fruit: ${fruit.getName()} (${fruit.getWeight()}kg) - Fresh and healthy!`);
  }
  
  visitElectronic(electronic: any): void {
    console.log(`Electronic: ${electronic.getBrand()} ${electronic.getModel()} - High-tech gadget!`);
  }
}

export class TaxCalculator implements Visitor {
  private totalTax: number = 0;
  
  visitBook(book: any): void {
    const tax = book.getPrice() * 0.05;
    this.totalTax += tax;
    console.log(`Book tax: $${tax}`);
  }
  
  visitFruit(fruit: any): void {
    const tax = fruit.getPrice() * 0.02;
    this.totalTax += tax;
    console.log(`Fruit tax: $${tax}`);
  }
  
  visitElectronic(electronic: any): void {
    const tax = electronic.getPrice() * 0.10;
    this.totalTax += tax;
    console.log(`Electronic tax: $${tax}`);
  }
  
  getTotalTax(): number {
    return this.totalTax;
  }
}

export class ShoppingCart {
  private items: Item[] = [];
  
  addItem(item: Item): void {
    this.items.push(item);
  }
  
  acceptVisitor(visitor: Visitor): void {
    for (const item of this.items) {
      item.accept(visitor);
    }
  }
}
