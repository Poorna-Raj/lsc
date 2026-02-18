const portSelect = document.getElementById("comPort");
const baudRate = document.getElementById("baudRate");
const btnPortsRefresh = document.getElementById("refreshPortsBtn");

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

populatePorts();
