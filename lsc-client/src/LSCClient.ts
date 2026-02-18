import { SerialManager } from "./serial/SerialManager.js";
import { LSCProtocol } from "./protocol/LSCProtocol.js";

type EdgeHandler = (pin: number, type: "RISING" | "FALLING") => void;

export default class LSCClient {
  private serial: SerialManager;
  private edgeHandler: EdgeHandler[] = [];

  constructor(port: string, baudRate: number) {
    this.serial = new SerialManager(port, baudRate);
  }

  async connect() {
    await this.serial.open(this.handleLine.bind(this));
  }

  private handleLine(line: string) {
    if (line.startsWith("EDGE")) {
      const [, type, pin] = line.split(":");
      this.edgeHandler.forEach((h) => {
        h(Number(pin), type as any);
      });
    }
  }

  onEdge(handler: EdgeHandler) {
    this.edgeHandler.push(handler);
  }

  setPinMode(pin: number, mode: "INPUT" | "OUTPUT") {
    this.serial.send(LSCProtocol.setPin(pin, mode));
  }

  writeDigital(pin: number, mode: "HIGH" | "LOW") {
    this.serial.send(LSCProtocol.writeDigital(pin, mode));
  }

  readDigital(pin: number) {
    this.serial.send(LSCProtocol.digitalRead(pin));
  }

  readAnalog(pin: number) {
    this.serial.send(LSCProtocol.analogRead(pin));
  }

  writeAnalog(pin: number, value: number) {
    this.serial.send(LSCProtocol.analogWrite(pin, value));
  }

  digitalWatch(pin: number) {
    this.serial.send(LSCProtocol.watchDigital(pin));
  }

  digitalUnWatch(pin: number) {
    this.serial.send(LSCProtocol.unWatchDigital(pin));
  }
}
