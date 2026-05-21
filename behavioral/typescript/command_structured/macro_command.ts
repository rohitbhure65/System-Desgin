import { Command } from './interfaces';

export class MacroCommand implements Command {
  private commands: Command[] = [];
  
  addCommand(command: Command): void {
    this.commands.push(command);
  }
  
  execute(): void {
    for (const command of this.commands) {
      command.execute();
    }
  }
  
  undo(): void {
    for (let i = this.commands.length - 1; i >= 0; i--) {
      this.commands[i].undo();
    }
  }
}
