const LSCClient = require("./LSCClient");

(async () => {
  const lsc = new LSCClient("COM11", 9600);

  await lsc.connect();

  lsc.setPinMode(4, "OUTPUT");
  lsc.writeDigital(4, "HIGH");

  lsc.onEdge((pin: number, type: "RISING" | "FALLING") => {
    console.log("EDGE", pin, type);
  });

  lsc.setPinMode(2, "INPUT");
  lsc.digitalWatch(2);
})();
