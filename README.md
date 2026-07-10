# Yuki - AI Quadruped Robot

<img width="960" height="708" alt="yuki" src="https://github.com/user-attachments/assets/6900968c-738c-4376-9b2d-6b81331a7623" />

Yuki is a small, endearing quadruped companion robot with an AI personality. Talk to it in
plain language and it responds (with a bit of attitude) and acts — walking, dancing,
waving, doing pushups, and more.

The project has two halves:

- **Firmware** (`Hardware/`) — an ESP32 drives 8 servos through a PCA9685 PWM board. It runs
  a WiFi web server that hosts a captive-portal control page and a small HTTP API
  (`/cmd?go=…`, `/cmd?pose=…`, `/cmd?stop=1`, `/status`, `/getSettings`). Movement
  choreographies live in `movement-sequences.h`.
- **Companion app** (`Yuki-companion-app/`) — a Python voice/text interface that uses an LLM
  (Google Gemini or a local Ollama/LM Studio model) to interpret what you say into a robot
  command + spoken reply, then sends it over WiFi. See its
  [README](Yuki-companion-app/README.md).

## Hardware

- ESP32 dev board
- PCA9685 16-channel PWM/servo driver (I²C on pins 21/22)
- 8 servos — two per leg across four legs
- Servo power supply (do **not** power servos from the ESP32)

## Firmware variants (`Hardware/`)

- **`yuki-firmware-main_wifi/`** — the maintained build. `AP+STA` WiFi (its own
  `Yuki's-Controller` access point **and** joins your network), mDNS (`yuki.local`),
  per-servo home calibration, and `/status` + `/getSettings` endpoints.
- **`yuki-firmware-main_remote/`** — an older access-point-only variant kept for reference.
- **`debugging-firmware/`** — a standalone servo tester.

### Building

Open the `.ino` in the Arduino IDE (or `arduino-cli`) with the **ESP32** board package and
these libraries: `Adafruit PWMServoDriver`, plus the bundled `WiFi` / `WebServer` /
`DNSServer` / `ESPmDNS`.

WiFi credentials are kept out of source: copy
`Hardware/yuki-firmware-main_wifi/secrets.example.h` to `secrets.h` and fill in your
network and access-point details before flashing (`secrets.h` is gitignored).

## Quick start

1. Flash the `_wifi` firmware (after creating `secrets.h`).
2. Power on Yuki; find it at `yuki.local` or read its IP from the serial monitor (115200 baud).
3. Run the companion app:
   ```powershell
   cd Yuki-companion-app
   pip install -r requirements.txt
   copy .env.example .env   # then edit .env
   python yuki_companion.py
   ```

No hardware yet? Set `YUKI_ROBOT_IP=mock` to drive the app without a robot.

## License

See [LICENSE](LICENSE).
