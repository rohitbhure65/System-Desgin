export interface Mediator {
  sendMessage(message: string, sender: string): void;
}

export abstract class Colleague {
  protected mediator: Mediator;
  protected name: string;
  
  constructor(mediator: Mediator, name: string) {
    this.mediator = mediator;
    this.name = name;
  }
  
  send(message: string): void {
    this.mediator.sendMessage(message, this.name);
  }
  
  abstract receive(message: string): void;
  
  getName(): string {
    return this.name;
  }
}
