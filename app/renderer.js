const portSelect = document.getElementById("comPort");
const baudRate = document.getElementById("baudRate");

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

populatePorts();
