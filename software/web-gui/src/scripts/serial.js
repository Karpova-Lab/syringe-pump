// Serial port and UI elements
let port;
const connectButton = document.getElementById("connectButton");
const pumpCardsContainer = document.getElementById("pump_cards_container");
const textDecoder = new TextDecoder();

// USB device filters
const USB_FILTERS = [
    { usbVendorId: 0x10C4, usbProductId: 0xEA60 } // CP2102N USB-to-UART Bridge Controller
];

// Override requestPort to use filters
const originalRequestPort = navigator.serial.requestPort;
navigator.serial.requestPort = function() {
    return originalRequestPort.call(this, { filters: USB_FILTERS });
};

// Helper function to write serial commands
async function writeSerialCommand(command) {
    try {
        const writer = port.writable.getWriter();
        await writer.write(new TextEncoder().encode(command));
        console.log("Sent command:", command);
        writer.releaseLock();
    } catch (err) {
        console.error("Error writing serial:", err);
    }
}

// Helper function to update pump settings UI
function updatePumpSettings(pump, settings) {
    const [flow_rate, id, steps, lead] = settings;
    const elements = [
        document.getElementById(`${pump}-mm inner diameter`), 
        document.getElementById(`${pump}-mL/min flow rate`)
    ];
    
    const values = [id,flow_rate];
    
    elements.forEach((element, i) => {
        if (element) {
            element.value = values[i];
            // Update corresponding slider if it exists
            const slider = document.getElementById(`${element.id}-slider`);
            if (slider) {
                slider.value = values[i];
            }
            element.style.transition = 'border-color 0.2s';
            element.style.borderColor = '#4f46e5'; // Indigo color
            setTimeout(() => {
                element.style.borderColor = ''; 
            }, 500);
        }
    });
}

// Connect button handler
connectButton.addEventListener("click", async () => {
    try {
        port = await navigator.serial.requestPort();
        await port.open({
            baudRate: 115200,
            dataBits: 8,
            stopBits: 1,
            parity: "none",
        });
        
        readSerialData();
        
        // Update UI to show connected state
        connectButton.textContent = "Connected";
        connectButton.classList.replace("bg-blue-500", "bg-green-500");
        connectButton.classList.remove("hover:bg-blue-600");
        pumpCardsContainer.classList.remove("opacity-50", "pointer-events-none");
        connectButton.style.display = "none";
        await writeSerialCommand(`settings;l2\n`);
        await writeSerialCommand(`settings;l1\n`);
        await writeSerialCommand(`settings;r1\n`);
        await writeSerialCommand(`settings;r2\n`);
    } catch (err) {
        alert("Failed to connect. Please check that the device is plugged in and no other programs are using it.");
        console.error("Error:", err);
    }
});

// Serial data reader
async function readSerialData() {
    if (!port?.readable) {
        console.error('Port is not open or readable');
        return;
    }

    const reader = port.readable.getReader();
    let buffer = '';

    try {
        while (true) {
            const { value, done } = await reader.read();
            if (done) break;
            
            if (value) {
                buffer += textDecoder.decode(value);
                const newlineIndex = buffer.indexOf('\n');

                if (newlineIndex !== -1) {
                    const response = buffer.slice(0, newlineIndex);
                    buffer = buffer.slice(newlineIndex + 1);

                    console.log("Response:", response);

                    if (response.includes('=')) {
                        const [pump, settingsStr] = response.split('=');
                        const settingsObj = JSON.parse(settingsStr.replace(/'/g, '"').replace(/None/g, 'null'));
                        const settings = [
                            settingsObj.flow_rate,
                            settingsObj.syringe_id_mm,
                            settingsObj.steps_per_rev,
                            settingsObj.lead_mm
                        ];
                        updatePumpSettings(pump, settings);
                    }
                }
            }
        }
    } catch (error) {
        console.error('Error reading serial:', error);
    } finally {
        reader.releaseLock();
    }
}

// Button event handlers
function setupPumpButtons() {
    // Infuse buttons
    document.querySelectorAll(".infuse-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            const volume = document.getElementById(`${pump}-mL`).value * 1000;
            await writeSerialCommand(`dispense;${pump};${volume}\n`);
        });
    });

    // Retract buttons
    document.querySelectorAll(".retract-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            const volume = document.getElementById(`${pump}-mL`).value * -1000;
            await writeSerialCommand(`dispense;${pump};${volume}\n`);
        });
    });

    // Home buttons
    document.querySelectorAll(".home-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            await writeSerialCommand(`dispense;${pump};-60000\n`);
        });
    });

    // Set buttons
    document.querySelectorAll(".set-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            const id = document.getElementById(`${pump}-mm inner diameter`).value;
            const flow_rate = document.getElementById(`${pump}-mL/min flow rate`).value;
            await writeSerialCommand(
                `diameter;${pump};${id}\n`
            );
            await writeSerialCommand(
                `flow_rate;${pump};${flow_rate}\n`
            );
        });
    });

    // Get buttons
    document.querySelectorAll(".get-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            await writeSerialCommand(`settings;${pump}\n`);
        });
    });
    // Stop buttons
    document.querySelectorAll(".stop-btn").forEach(button => {
        button.addEventListener("click", async () => {
            const pump = button.id.split("-")[0];
            await writeSerialCommand(`stop;${pump}\n`);
        });
    });
}

// Initialize button handlers
setupPumpButtons();