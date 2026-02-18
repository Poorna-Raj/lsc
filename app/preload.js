const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("api", {
  getComPorts: () => ipcRenderer.invoke("get-com-ports"),
});
