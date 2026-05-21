import { Command } from './interfaces';

export class RemoteControl {
  private commandHistory: Command[] = [];
  private undoStack: Command[] = [];
  
  setCommand(command: Command): void {
    this.commandHistory.push(command);
  }
  
  buttonPressed(slot: number): void {
    if (slot < this.commandHistory.length) {
      this.commandHistory[slot].execute();
      this.undoStack.push(this.commandHistory[slot]);
    }
  }
  
  undoButtonPressed(): void {
    if (this.undoStack.length > 0) {
      const command = this.undoStack.pop()!;
      command.undo();
    } else {
      console.log('Nothing to undo');
    }
  }
}
