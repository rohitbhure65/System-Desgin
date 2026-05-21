import { Mediator } from './interfaces';

export class Aircraft {
  protected controlTower: Mediator;
  protected flightNumber: string;
  protected altitude: number = 0;
  
  constructor(tower: Mediator, flightNumber: string) {
    this.controlTower = tower;
    this.flightNumber = flightNumber;
  }
  
  requestTakeoff(): void {
    console.log(`${this.flightNumber} requesting takeoff clearance...`);
  }
  
  requestLanding(): void {
    console.log(`${this.flightNumber} requesting landing clearance...`);
  }
  
  setAltitude(alt: number): void {
    this.altitude = alt;
    console.log(`${this.flightNumber} at altitude ${this.altitude} feet`);
  }
  
  getFlightNumber(): string {
    return this.flightNumber;
  }
}

export class ControlTower implements Mediator {
  private aircrafts: Map<string, Aircraft> = new Map();
  
  registerAircraft(aircraft: Aircraft): void {
    this.aircrafts.set(aircraft.getFlightNumber(), aircraft);
  }
  
  sendMessage(message: string, sender: string): void {
    console.log(`Control Tower: ${message} from ${sender}`);
  }
  
  grantTakeoff(flightNumber: string): void {
    console.log(`Control Tower: Takeoff granted to ${flightNumber}`);
    const aircraft = this.aircrafts.get(flightNumber);
    if (aircraft) {
      aircraft.setAltitude(10000);
    }
  }
  
  grantLanding(flightNumber: string): void {
    console.log(`Control Tower: Landing granted to ${flightNumber}`);
    const aircraft = this.aircrafts.get(flightNumber);
    if (aircraft) {
      aircraft.setAltitude(0);
    }
  }
}
