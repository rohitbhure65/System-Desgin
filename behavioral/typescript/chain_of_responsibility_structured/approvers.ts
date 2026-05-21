import { Approver } from './interfaces';

export class TeamLead extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 1000) {
      console.log(`TeamLead: Approved request of $${amount}`);
    } else {
      console.log('TeamLead: Amount exceeds limit, passing to manager...');
      this.passRequest(amount);
    }
  }
}

export class ManagerApprover extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 5000) {
      console.log(`Manager: Approved request of $${amount}`);
    } else {
      console.log('Manager: Amount exceeds limit, passing to director...');
      this.passRequest(amount);
    }
  }
}

export class Director extends Approver {
  approveRequest(amount: number): void {
    if (amount <= 20000) {
      console.log(`Director: Approved request of $${amount}`);
    } else {
      console.log('Director: Amount exceeds limit, passing to CEO...');
      this.passRequest(amount);
    }
  }
}

export class CEO extends Approver {
  approveRequest(amount: number): void {
    console.log(`CEO: Approved request of $${amount} (final approver)`);
  }
}
