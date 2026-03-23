#pragma once

#include <Arduino.h>

// ======================================================================
// --- WEB INTERFACE HTML ---
// ======================================================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Yuki's Access Point Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    :root {
        --accent: #7dd3fc;
        --glass-bg: rgba(255,255,255,0.08);
        --glass-border: rgba(255,255,255,0.2);
    }

    *{
        user-select:none;
    }

    body{
        font-family:'Segoe UI',sans-serif;
        text-align:center;
        margin:0;
        padding:20px;

        background:
            radial-gradient(circle at 20% 20%, #1f2937, #020617),
            radial-gradient(circle at 80% 80%, #0f172a, #000);

        color:white;
    }

    /* Title */

    h2{
        font-size:32px;
        font-weight:600;
        margin-bottom:20px;
    }

    /* Glass panels */

    .section{
        background:var(--glass-bg);

        backdrop-filter:blur(25px);
        -webkit-backdrop-filter:blur(25px);

        border:1px solid var(--glass-border);
        border-radius:18px;

        padding:20px;

        box-shadow:
        0 10px 30px rgba(0,0,0,0.5),
        inset 0 0 10px rgba(255,255,255,0.1);

        max-width:450px;
        margin:auto;
    }

    /* Layout */

    .sections-container{
        display:flex;
        flex-direction:column;
        gap:20px;
    }

    .section-title{
        font-size:14px;
        letter-spacing:1px;
        margin-bottom:15px;
        color:#7dd3fc;
    }

    /* Buttons */

    button{

        background:rgba(255,255,255,0.08);

        border:1px solid rgba(255,255,255,0.2);

        backdrop-filter:blur(10px);

        border-radius:14px;

        color:white;

        padding:15px;

        font-size:18px;

        cursor:pointer;

        transition:all .2s;

        box-shadow:
        0 6px 20px rgba(0,0,0,0.5),
        inset 0 0 8px rgba(255,255,255,0.15);
    }

    button:hover{
        background:rgba(255,255,255,0.15);
        transform:translateY(-2px);
    }

    button:active{
        transform:translateY(2px);
    }

    /* Dpad */

    .dpad{
        display:grid;
        grid-template-columns:repeat(3,1fr);
        gap:10px;
    }

    .spacer{
        visibility:hidden;
    }

    .dpad button{
        font-size:32px;
    }

    /* Pose grid */

    .grid{
        display:grid;
        grid-template-columns:repeat(3,1fr);
        gap:10px;
    }

    /* Stop button */

    .btn-stop-all{
        background:rgba(255,80,80,0.2);
        border:1px solid rgba(255,120,120,0.6);
        margin-top:10px;
    }

    /* Gamepad status */

    .gamepad-status{
        margin-top:15px;
        padding:10px 16px;
        border-radius:10px;
        border:1px solid rgba(255,255,255,0.2);
        background:rgba(255,255,255,0.05);
    }

    .gamepad-status.connected{
        border:1px solid #22c55e;
        color:#22c55e;
    }

    /* Settings modal */

    .settings-panel{
        position:fixed;
        top:0;
        left:0;
        width:100%;
        height:100%;

        background:rgba(0,0,0,0.7);

        backdrop-filter:blur(10px);

        display:none;
    }

    .settings-content{

        background:var(--glass-bg);

        backdrop-filter:blur(25px);

        border:1px solid var(--glass-border);

        border-radius:20px;

        max-width:420px;

        margin:40px auto;

        padding:25px;
    }

    /* Inputs */

    .settings-content input,
    .settings-content select{

        width:100%;
        padding:10px;

        border-radius:10px;

        border:1px solid rgba(255,255,255,0.2);

        background:rgba(255,255,255,0.05);

        color:white;
    }

    /* Motor sliders */

    .motor-slider input[type=range]{
        width:100%;
        height:6px;
        background:rgba(255,255,255,0.2);
        border-radius:6px;
    }

    .motor-slider input[type=range]::-webkit-slider-thumb{
        appearance:none;
        width:18px;
        height:18px;
        border-radius:50%;
        background:#7dd3fc;
    }
  </style>
</head>
<body>
  <h2>Yuki's Controller</h2>
  <div class="command-queue" id="queueStatus">Command Queue: 0/3</div>
  
  <div class="sections-container">
    <div class="section-column">
      <!-- Movement Control Section -->
      <div class="section">
    <div class="section-title">Movement Control</div>
    <div class="dpad-container">
      <div class="dpad">
        <div class="spacer"></div>
        <button onmousedown="move('forward')" onmouseup="stop()" ontouchstart="move('forward')" ontouchend="stop()">&#9650;</button>
        <div class="spacer"></div>
        
        <button onmousedown="move('left')" onmouseup="stop()" ontouchstart="move('left')" ontouchend="stop()">&#9664;</button>
        <button onmousedown="move('backward')" onmouseup="stop()" ontouchstart="move('backward')" ontouchend="stop()">&#9660;</button>
        <button onmousedown="move('right')" onmouseup="stop()" ontouchstart="move('right')" ontouchend="stop()">&#9654;</button>
      </div>
      <button class="btn-stop-all" onclick="stop()">STOP ALL</button>
    </div>
  </div>

      <!-- Poses & Animations Section -->
      <div class="section">
        <div class="section-title">Poses & Animations</div>
        <div class="grid">
          <button class="btn-pose" onclick="pose('rest')">Rest</button>
          <button class="btn-pose" onclick="pose('stand')">Stand</button>
          <button class="btn-pose" onclick="pose('wave')">Wave</button>
          <button class="btn-pose" onclick="pose('dance')">Dance</button>
          <button class="btn-pose" onclick="pose('swim')">Swim</button>
          <button class="btn-pose" onclick="pose('point')">Point</button>
          <button class="btn-pose" onclick="pose('pushup')">Pushup</button>
          <button class="btn-pose" onclick="pose('bow')">Bow</button>
          <button class="btn-pose" onclick="pose('cute')">Cute</button>
          <button class="btn-pose" onclick="pose('freaky')">Freaky</button>
          <button class="btn-pose" onclick="pose('worm')">Worm</button>
          <button class="btn-pose" onclick="pose('shake')">Shake</button>
          <button class="btn-pose" onclick="pose('shrug')">Shrug</button>
          <button class="btn-pose" onclick="pose('dead')">Dead</button>
          <button class="btn-pose" onclick="pose('crab')">Crab</button>
        </div>
      </div>
    </div>

    <div class="section-column">
      <!-- Settings & Status Section -->
      <div class="section">
        <div class="section-title">System</div>
        <button class="btn-settings" onclick="openSettings()">Settings</button>
        <div style="margin-top: 15px;">
          <div id="gamepadStatus" class="gamepad-status">Gamepad disconnected</div>
        </div>
      </div>
    </div>
  </div>

  <div id="settingsPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Settings</h3>
      
      <div class="settings-section">
        <h4>Animation Parameters</h4>
        <label>Frame Delay (ms):</label>
        <input type="number" id="frameDelay" min="1" max="1000" step="1">
        <label>Walk Cycles:</label>
        <input type="number" id="walkCycles" min="1" max="50" step="1">
      </div>

      <div class="settings-section">
        <h4>Motor Settings</h4>
        <label>Motor Current Delay (ms):</label>
        <input type="number" id="motorCurrentDelay" min="0" max="500" step="1">
        <label>Motor Speed:</label>
        <select id="motorSpeed">
          <option value="slow">Slow</option>
          <option value="medium" selected>Medium</option>
          <option value="fast">Fast</option>
        </select>
      </div>

      <div class="settings-section">
        <h4>Theme</h4>
        <label>Accent Color:</label>
        <select id="themeColor">
          <option value="#ff8c42">Orange (Default)</option>
          <option value="#66d9ef">Cyan</option>
          <option value="#a8dadc">Light Blue</option>
          <option value="#2ecc71">Green</option>
          <option value="#e74c3c">Red</option>
          <option value="#9b59b6">Purple</option>
          <option value="#f39c12">Yellow</option>
          <option value="#e91e63">Pink</option>
          <option value="custom">Custom</option>
        </select>
        <input type="color" id="customColor" value="#ff8c42" style="margin-top: 10px; display: none;">
      </div>

      <button class="btn-settings" style="width: 100%; margin-top: 20px;" onclick="openMotorControl()">Manual Motor Control</button>

      <button class="btn-save" onclick="saveSettings()">Save Settings</button>
      <button class="btn-close" onclick="closeSettings()">Close</button>
    </div>
  </div>

  <div id="motorControlPanel" class="settings-panel">
    <div class="settings-content">
      <h3>Manual Motor Control</h3>
      <div class="lock-indicator" id="lockIndicator">Locked during animations</div>
      
      <div class="settings-section">
        <div class="motor-controls">
          <div class="motor-slider">
            <label><span>S0 R1</span><span id="m1val">90&deg;</span></label>
            <input type="range" id="motor1" min="0" max="180" value="90" oninput="updateMotor(1, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S1 R2</span><span id="m2val">90&deg;</span></label>
            <input type="range" id="motor2" min="0" max="180" value="90" oninput="updateMotor(2, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S2 L1</span><span id="m3val">90&deg;</span></label>
            <input type="range" id="motor3" min="0" max="180" value="90" oninput="updateMotor(3, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S3 L2</span><span id="m4val">90&deg;</span></label>
            <input type="range" id="motor4" min="0" max="180" value="90" oninput="updateMotor(4, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S4 R4</span><span id="m5val">90&deg;</span></label>
            <input type="range" id="motor5" min="0" max="180" value="90" oninput="updateMotor(5, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S5 R3</span><span id="m6val">90&deg;</span></label>
            <input type="range" id="motor6" min="0" max="180" value="90" oninput="updateMotor(6, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S6 L3</span><span id="m7val">90&deg;</span></label>
            <input type="range" id="motor7" min="0" max="180" value="90" oninput="updateMotor(7, this.value)">
          </div>
          <div class="motor-slider">
            <label><span>S7 L4</span><span id="m8val">90&deg;</span></label>
            <input type="range" id="motor8" min="0" max="180" value="90" oninput="updateMotor(8, this.value)">
          </div>
        </div>
      </div>

      <button class="btn-close" onclick="closeMotorControl()">Close</button>
    </div>
  </div>

<script>
// Command queue management - max 3 commands
let commandQueue = 0;
const MAX_COMMANDS = 3;
let motorsLocked = false;

// Load theme on page load
document.addEventListener('DOMContentLoaded', () => {
  loadTheme();
});

function loadTheme() {
  const savedColor = localStorage.getItem('themeColor');
  if (savedColor) {
    applyTheme(savedColor);
  }
}

function applyTheme(color) {
  const root = document.documentElement;
  root.style.setProperty('--content-color', color);
  
  // Calculate darker shades
  const rgb = hexToRgb(color);
  if (rgb) {
    const dark = `rgb(${Math.max(0, rgb.r - 20)}, ${Math.max(0, rgb.g - 20)}, ${Math.max(0, rgb.b - 20)})`;
    const darker = `rgb(${Math.max(0, rgb.r - 40)}, ${Math.max(0, rgb.g - 40)}, ${Math.max(0, rgb.b - 40)})`;
    const glow = `rgba(${rgb.r}, ${rgb.g}, ${rgb.b}, 0.3)`;
    
    root.style.setProperty('--content-color-dark', dark);
    root.style.setProperty('--content-color-darker', darker);
    root.style.setProperty('--content-color-glow', glow);
  }
}

function hexToRgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

function updateQueueStatus() {
  const queueEl = document.getElementById('queueStatus');
  queueEl.textContent = `Command Queue: ${commandQueue}/${MAX_COMMANDS}`;
  if (commandQueue >= MAX_COMMANDS) {
    queueEl.classList.add('full');
  } else {
    queueEl.classList.remove('full');
  }
}

function canSendCommand() {
  return commandQueue < MAX_COMMANDS;
}

function incrementQueue() {
  commandQueue++;
  updateQueueStatus();
  setTimeout(() => {
    if (commandQueue > 0) {
      commandQueue--;
    }
    updateQueueStatus();
  }, 1000);
}

function lockMotors(duration = 3000) {
  motorsLocked = true;
  document.getElementById('lockIndicator').classList.add('active');
  for (let i = 1; i <= 8; i++) {
    const slider = document.getElementById('motor' + i);
    if (slider) slider.disabled = true;
  }
  setTimeout(() => {
    motorsLocked = false;
    document.getElementById('lockIndicator').classList.remove('active');
    for (let i = 1; i <= 8; i++) {
      const slider = document.getElementById('motor' + i);
      if (slider) slider.disabled = false;
    }
  }, duration);
}

function move(dir) { 
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?go=' + dir).catch(console.log); 
}

function stop() { 
  commandQueue = 0;
  updateQueueStatus();
  fetch('/cmd?stop=1').catch(console.log); 
}

function pose(name) { 
  if (!canSendCommand()) return;
  incrementQueue();
  lockMotors(3000);
  fetch('/cmd?pose=' + name).catch(console.log); 
}

function updateMotor(motorNum, value) {
  if (motorsLocked) return;
  document.getElementById('m' + motorNum + 'val').textContent = value + '\u00B0';
  if (!canSendCommand()) return;
  incrementQueue();
  fetch('/cmd?motor=' + motorNum + '&value=' + value).catch(console.log);
}

function openSettings() {
  fetch('/getSettings').then(r => r.json()).then(data => {
    document.getElementById('frameDelay').value = data.frameDelay || 100;
    document.getElementById('walkCycles').value = data.walkCycles || 10;
    document.getElementById('motorCurrentDelay').value = data.motorCurrentDelay || 20;
    document.getElementById('motorSpeed').value = data.motorSpeed || 'medium';
    
    // Load theme settings
    const savedColor = localStorage.getItem('themeColor') || '#ff8c42';
    const colorSelect = document.getElementById('themeColor');
    const customColorInput = document.getElementById('customColor');
    
    // Check if saved color matches a preset
    let matchFound = false;
    for (let option of colorSelect.options) {
      if (option.value === savedColor) {
        colorSelect.value = savedColor;
        matchFound = true;
        break;
      }
    }
    
    if (!matchFound) {
      colorSelect.value = 'custom';
      customColorInput.value = savedColor;
      customColorInput.style.display = 'block';
    }
    
    document.getElementById('settingsPanel').style.display = 'block';
  }).catch(() => {
    // Fallback if settings endpoint doesn't exist yet
    document.getElementById('frameDelay').value = 100;
    document.getElementById('walkCycles').value = 10;
    document.getElementById('motorCurrentDelay').value = 20;
    
    const savedColor = localStorage.getItem('themeColor') || '#ff8c42';
    document.getElementById('themeColor').value = savedColor;
    
    document.getElementById('settingsPanel').style.display = 'block';
  });
  
  // Add event listener for theme color change
  document.getElementById('themeColor').addEventListener('change', function() {
    const customColorInput = document.getElementById('customColor');
    if (this.value === 'custom') {
      customColorInput.style.display = 'block';
    } else {
      customColorInput.style.display = 'none';
      applyTheme(this.value);
    }
  });
  
  document.getElementById('customColor').addEventListener('input', function() {
    applyTheme(this.value);
  });
}

function closeSettings() { 
  document.getElementById('settingsPanel').style.display = 'none'; 
}

function openMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'block';
}

function closeMotorControl() {
  document.getElementById('motorControlPanel').style.display = 'none';
}

function saveSettings() {
  const fd = document.getElementById('frameDelay').value;
  const wc = document.getElementById('walkCycles').value;
  const mcd = document.getElementById('motorCurrentDelay').value;
  const ms = document.getElementById('motorSpeed').value;
  
  // Save theme color
  const colorSelect = document.getElementById('themeColor');
  const customColorInput = document.getElementById('customColor');
  const themeColor = colorSelect.value === 'custom' ? customColorInput.value : colorSelect.value;
  localStorage.setItem('themeColor', themeColor);
  applyTheme(themeColor);
  
  fetch(`/setSettings?frameDelay=${fd}&walkCycles=${wc}&motorCurrentDelay=${mcd}&motorSpeed=${ms}`)
    .then(() => closeSettings())
    .catch(() => closeSettings());
}

let activeGamepadIndex = null;
let gamepadPollId = null;
let lastButtonStates = [];
let lastAxisDir = { x: 0, y: 0 };
const axisThreshold = 0.5;
const pollIntervalMs = 80;

const buttonBindings = {
  0: () => pose('stand'),   // A / Cross
  1: () => pose('wave'),    // B / Circle
  2: () => pose('dance'),   // X / Square
  3: () => pose('swim'),    // Y / Triangle
  4: () => pose('point'),   // LB / L1
  5: () => pose('pushup'),  // RB / R1
  6: () => pose('bow'),     // LT / L2
  7: () => pose('shake'),   // RT / R2
  8: () => stop(),          // Back / Share
  9: () => pose('rest'),    // Start / Options
  10: () => pose('cute'),   // L3
  11: () => pose('freaky'), // R3
  12: () => move('forward'),// D-pad up
  13: () => move('backward'),// D-pad down
  14: () => move('left'),   // D-pad left
  15: () => move('right'),  // D-pad right
  16: () => stop(),         // Home / PS
  17: () => pose('worm')    // Touchpad / extra
};

const buttonReleaseStop = new Set([12, 13, 14, 15]);

function updateGamepadStatus(connected) {
  const status = document.getElementById('gamepadStatus');
  if (!status) return;
  if (connected) {
    status.textContent = 'Gamepad connected';
    status.classList.add('connected');
  } else {
    status.textContent = 'Gamepad disconnected';
    status.classList.remove('connected');
  }
}

function handleButtonChange(index, pressed) {
  if (pressed) {
    const action = buttonBindings[index];
    if (action) action();
  } else if (buttonReleaseStop.has(index)) {
    stop();
  }
}

function getAxisDirection(x, y) {
  if (Math.abs(x) < axisThreshold && Math.abs(y) < axisThreshold) return { x: 0, y: 0 };
  if (Math.abs(x) > Math.abs(y)) {
    return { x: x > 0 ? 1 : -1, y: 0 };
  }
  return { x: 0, y: y > 0 ? 1 : -1 };
}

function applyAxisDirection(dir) {
  if (dir.x === 1) move('right');
  else if (dir.x === -1) move('left');
  else if (dir.y === 1) move('backward');
  else if (dir.y === -1) move('forward');
  else stop();
}

function pollGamepad() {
  const pads = navigator.getGamepads ? navigator.getGamepads() : [];
  const pad = pads && activeGamepadIndex !== null ? pads[activeGamepadIndex] : null;
  if (!pad) {
    updateGamepadStatus(false);
    return;
  }
  updateGamepadStatus(true);

  if (!lastButtonStates.length) {
    lastButtonStates = pad.buttons.map(b => !!b.pressed);
  }
  pad.buttons.forEach((btn, i) => {
    const pressed = !!btn.pressed;
    if (pressed !== lastButtonStates[i]) {
      handleButtonChange(i, pressed);
      lastButtonStates[i] = pressed;
    }
  });

  const x = pad.axes[0] || 0;
  const y = pad.axes[1] || 0;
  const dir = getAxisDirection(x, y);
  if (dir.x !== lastAxisDir.x || dir.y !== lastAxisDir.y) {
    applyAxisDirection(dir);
    lastAxisDir = dir;
  }
}

window.addEventListener('gamepadconnected', (e) => {
  activeGamepadIndex = e.gamepad.index;
  lastButtonStates = [];
  lastAxisDir = { x: 0, y: 0 };
  updateGamepadStatus(true);
  if (!gamepadPollId) {
    gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
  }
});

window.addEventListener('gamepaddisconnected', (e) => {
  if (activeGamepadIndex === e.gamepad.index) {
    activeGamepadIndex = null;
    lastButtonStates = [];
    lastAxisDir = { x: 0, y: 0 };
    updateGamepadStatus(false);
  }
});

if (navigator.getGamepads) {
  setInterval(() => {
    if (activeGamepadIndex !== null) return;
    const pads = navigator.getGamepads();
    if (!pads) return;
    for (let i = 0; i < pads.length; i++) {
      if (pads[i]) {
        activeGamepadIndex = pads[i].index;
        updateGamepadStatus(true);
        if (!gamepadPollId) {
          gamepadPollId = setInterval(pollGamepad, pollIntervalMs);
        }
        break;
      }
    }
  }, 1000);
}
</script>
</body>
</html>
)rawliteral";
