const portSelect = document.getElementById("comPort");
const baudRate = document.getElementById("baudRate");
const btnPortsRefresh = document.getElementById("refreshPortsBtn");
const btnConnect = document.getElementById("connectBtn");
const connectStatus = document.getElementById("connStatus");
const statusDot = document.getElementById("statusDot");

async function populatePorts() {
  const ports = await window.api.getComPorts();

  portSelect.innerHTML = "";

  ports.forEach((p) => {
    const option = document.createElement("option");
    option.value = p;
    option.text = p;
    portSelect.appendChild(option);
  });
}

btnPortsRefresh.addEventListener("click", async () => {
  populatePorts();
});

btnConnect.addEventListener("click", async () => {
  const port = portSelect.value;
  const baud = Number(baudRate.value);

  if (!port || !baud) {
    console.log("Undefined port or baud rate!");
    return;
  }

  try {
    await window.api.connect(port, baud);
    connectStatus.textContent = "● Connected";
    connectStatus.classList.add("connected");
    statusDot.classList.add("status-dot--active");
    console.log("Connected to", port, "at", baud);
  } catch (err) {
    console.error("Connection Failed:", err);
  }
});

populatePorts();
