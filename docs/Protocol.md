# LSC Serial Protocol v1

## Transport
- Baud: 9600
- Newline-terminated commands

## Commands

### Pin Mode

`SET_PIN:<pin>:<mode>`

- mode: 0 = **INPUT**
- mode: 1 = **OUTPUT**

### Digital Write

`WRITE_DIGITAL:<pin>:<value>`

- mode: 0 = **LOW**
- mode: 1 = **HIGH**

### Digital Read

`READ_DIGITAL:<pin>`

- Only for **digital pins**.

### Analog Read

`READ_ANALOG:<pin>`

- Only for **analog pins**.

### Analog Write

`WRITE_ANALOG:<pin>:<value>`

- value: **0 to 255**

### Edge Detection

`WATCH_DIGITAL:<pin>`

- Only for **digital pins**.

### Reverse Edge Detection

`UNWATCH_DIGITAL:<pin>`

- To deselect the `WATCH_DIGITAL:<pin>`.