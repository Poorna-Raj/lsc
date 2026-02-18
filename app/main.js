const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("node:path");
const { SerialPort } = require("serialport");

const createWindow = () => {
  const win = new BrowserWindow({
    width: 1080,
    height: 720,
    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      contextIsolation: true,
      nodeIntegration: false,
      sandbox: false,
    },
  });

  // win.setMenu(null);

  win.loadFile("index.html");
};

ipcMain.handle("get-com-ports", async () => {
  const ports = await SerialPort.list();
  return ports.map((port) => port.path);
});

app.whenReady().then(() => {
  createWindow();

  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});
