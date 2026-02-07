import {SerialPort} from "serialport"
import {ReadlineParser} from "@serialport/parser-readline"

export class SerialManager{
    private port!: SerialPort;
    private parser!: ReadlineParser;

    constructor(
        private path:string,
        private baudRate = 9600
    ){}

    open(onData:(line:string) => void){
        this.port = new SerialPort({
            path:this.path,
            baudRate:this.baudRate,
            autoOpen:false
        });

        this.parser = this.port.pipe(
            new ReadlineParser({delimiter:"\n"})
        );

        this.parser.on("data",onData);

        return new Promise<void>((resolve,reject) => {
            this.port.open(err => {
                if(err) reject(err);
                else resolve();
            });
        });
    }

    send(cmd: string) {
        this.port.write(cmd + "\n");
    }

    close() {
        this.port.close();
    }
}