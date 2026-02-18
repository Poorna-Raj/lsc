const { contextBridge, ipcRenderer } = require("electron");
const LSCClient = require("../lsc-client/dist/LSCClient.js").default;
let client = null;

contextBridge.exposeInMainWorld("api", {
  getComPorts: () => ipcRenderer.invoke("get-com-ports"),
  connect: async (port, baud) => {
    client = new LSCClient(port, baud);
    await client.connect();
  },
  getClient: () => {
    return client;
  },
});
