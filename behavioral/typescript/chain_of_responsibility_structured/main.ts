import { Handler } from './interfaces';
import { SupportAgent, TechnicalSpecialist, Manager } from './handlers';
import { TeamLead, ManagerApprover, Director, CEO } from './approvers';
import { ConsoleLogger, FileLogger, ErrorLogger } from './loggers';

console.log('=== Chain of Responsibility Pattern Demo ===\n');

// Example 1: Customer Service Chain
console.log('--- Customer Service Chain ---');

const agent = new SupportAgent();
const specialist = new TechnicalSpecialist();
const manager = new Manager();

agent.setNext(specialist).setNext(manager);

console.log('\nRequest: basic_question');
agent.handle('basic_question');

console.log('\nRequest: complex_technical');
agent.handle('complex_technical');

console.log('\nRequest: refund');
agent.handle('refund');

console.log('\nRequest: unknown');
agent.handle('unknown');

console.log('');

// Example 2: Document Approval Chain
console.log('--- Document Approval Chain ---');

const teamLead = new TeamLead();
const manager2 = new ManagerApprover();
const director = new Director();
const ceo = new CEO();

teamLead.setNext(manager2).setNext(director).setNext(ceo);

console.log('\nRequest: $500');
teamLead.approveRequest(500);

console.log('\nRequest: $3000');
teamLead.approveRequest(3000);

console.log('\nRequest: $15000');
teamLead.approveRequest(15000);

console.log('\nRequest: $50000');
teamLead.approveRequest(50000);

console.log('');

// Example 3: Logging Chain
console.log('--- Logging Chain ---');

const consoleLogger = new ConsoleLogger();
const fileLogger = new FileLogger();
const errorLogger = new ErrorLogger();

consoleLogger.setNext(fileLogger).setNext(errorLogger);

console.log('\nLog: Info message (severity 1)');
consoleLogger.log('Info message', 1);

console.log('\nLog: Warning message (severity 2)');
consoleLogger.log('Warning message', 2);

console.log('\nLog: Error message (severity 3)');
consoleLogger.log('Error message', 3);
