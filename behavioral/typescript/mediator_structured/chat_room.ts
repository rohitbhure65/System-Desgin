import { Mediator, Colleague } from './interfaces';

export class User extends Colleague {
  constructor(mediator: Mediator, name: string) {
    super(mediator, name);
  }
  
  receive(message: string): void {
    console.log(`${this.name} received: ${message}`);
  }
}

export class Bot extends Colleague {
  constructor(mediator: Mediator, name: string) {
    super(mediator, name);
  }
  
  receive(message: string): void {
    console.log(`${this.name} received: ${message}`);
    this.send('Auto-reply: Thanks for your message!');
  }
}

export class ChatRoom implements Mediator {
  private colleagues: Map<string, Colleague> = new Map();
  
  addUser(colleague: Colleague): void {
    this.colleagues.set(colleague.getName(), colleague);
  }
  
  sendMessage(message: string, sender: string): void {
    console.log(`${sender} sends: ${message}`);
    for (const [name, colleague] of this.colleagues) {
      if (name !== sender) {
        colleague.receive(message);
      }
    }
  }
}
