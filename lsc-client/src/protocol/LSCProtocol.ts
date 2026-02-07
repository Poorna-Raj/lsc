export class LSCProtocol {
  static setPin(pin: number, mode: "INPUT" | "OUTPUT") {
    return `SET_PIN:${pin}:${mode == "INPUT" ? 1 : 0}`;
  }

  static writeDigital(pin: number, mode: "HIGH" | "LOW") {
    return `WRITE_DIGITAL:${pin}:${mode == "HIGH" ? 1 : 0}`;
  }

  static digitalRead(pin: number) {
    return `READ_DIGITAL:${pin}`;
  }

  static analogRead(pin: number) {
    return `READ_ANALOG:${pin}`;
  }

  static analogWrite(pin: number, value: number) {
    return `WRITE_ANALOG:${pin}:${value}`;
  }

  static watchDigital(pin: number) {
    return `WATCH_DIGITAL:${pin}`;
  }

  static unWatchDigital(pin: number) {
    return `UNWATCH_DIGITAL:${pin}`;
  }
}
