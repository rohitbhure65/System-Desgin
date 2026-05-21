import { Handler } from './interfaces';

export class SupportAgent extends Handler {
  handle(request: string): void {
    if (request === 'technical_issue' || request === 'basic_question') {
      console.log(`SupportAgent: Handling request - ${request}`);
    } else {
      console.log('SupportAgent: Passing to next handler...');
      this.passRequest(request);
    }
  }
}

export class TechnicalSpecialist extends Handler {
  handle(request: string): void {
    if (request === 'complex_technical' || request === 'bug_report') {
      console.log(`TechnicalSpecialist: Handling request - ${request}`);
    } else {
      console.log('TechnicalSpecialist: Passing to next handler...');
      this.passRequest(request);
    }
  }
}

export class Manager extends Handler {
  handle(request: string): void {
    if (request === 'refund' || request === 'complaint' || request === 'escalation') {
      console.log(`Manager: Handling request - ${request}`);
    } else {
      console.log('Manager: Passing to next handler...');
      this.passRequest(request);
    }
  }
}
