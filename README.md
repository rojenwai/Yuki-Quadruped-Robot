# Yuki — AI Quadruped Robot

[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)

Yuki is a small, endearing quadruped companion robot with an AI personality. Talk to it in
plain language and it responds (with a bit of attitude) and acts — walking, dancing,
waving, doing pushups, and more.

> **Credit:** Yuki's firmware is built on the excellent
> [**Sesame Robot**](https://github.com/dorianborian/sesame-robot) project by
> [Dorian Todd (@dorianborian)](https://github.com/dorianborian), used under the Apache
> License 2.0. See [Credit and modifications](#credit-and-modifications) for exactly what I
> changed.

The project has two halves:

- **Firmware** (`Hardware/`) — an ESP32 drives 8 servos through a PCA9685 PWM board. It runs
  a WiFi web server that hosts a captive-portal control page and a small HTTP API
  (`/cmd?go=…`, `/cmd?pose=…`, `/cmd?stop=1`, `/status`, `/getSettings`). Movement
  choreographies live in `movement-sequences.h`. *Derived from Sesame Robot.*
- **Companion app** (`Yuki-companion-app/`) — a Python voice/text interface that uses an LLM
  (Google Gemini or a local Ollama/LM Studio model) to interpret what you say into a robot
  command + spoken reply, then sends it over WiFi. *Original work.* See its
  [README](Yuki-companion-app/README.md).

## Hardware

- ESP32 dev board
- PCA9685 16-channel PWM/servo driver (I²C on pins 21/22)
- 8 servos — two per leg across four legs
- Servo power supply (do **not** power servos from the ESP32)

## Firmware variants (`Hardware/`)

- **`yuki-firmware-main/`** — the maintained build. `AP+STA` WiFi (its own
  `Yuki's-Controller` access point **and** joins your network), mDNS (`yuki.local`),
  per-servo home calibration, and `/status` + `/getSettings` endpoints.
- **`yuki-firmware-main_remote/`** — an older access-point-only variant kept for reference.
- **`debugging-firmware/`** — a standalone servo tester (serial `id,angle` commands).

### Building

Open the `.ino` in the Arduino IDE (or `arduino-cli`) with the **ESP32** board package and
these libraries: `Adafruit PWMServoDriver`, plus the bundled `WiFi` / `WebServer` /
`DNSServer` / `ESPmDNS`.

WiFi credentials are kept out of source: copy
`Hardware/yuki-firmware-main/secrets.example.h` to `secrets.h` and fill in your
network and access-point details before flashing (`secrets.h` is gitignored).

## Quick start

1. Flash `yuki-firmware-main` (after creating `secrets.h`).
2. Power on Yuki; find it at `yuki.local` or read its IP from the serial monitor (115200 baud).
3. Run the companion app:
   ```powershell
   cd Yuki-companion-app
   pip install -r requirements.txt
   copy .env.example .env   # then edit .env
   python yuki_companion.py
   ```

No hardware yet? Set `YUKI_ROBOT_IP=mock` to drive the app without a robot.

## Credit and modifications

The ESP32 firmware in `Hardware/` is a **modified derivative** of the firmware from the
[Sesame Robot](https://github.com/dorianborian/sesame-robot) project by Dorian Todd,
Copyright Dorian Todd, licensed under the Apache License 2.0. Full credit for the original
design — the pose/gait routines, the captive-portal control page, and the overall firmware
structure — belongs to that project.

Files derived from upstream (each carries a modification notice in its header):

| This repo | Upstream original |
|---|---|
| `Hardware/yuki-firmware-main/yuki-firmware-main.ino` | `firmware/sesame-firmware-main.ino` |
| `Hardware/yuki-firmware-main/captive-portal.h` | `firmware/captive-portal.h` |
| `Hardware/yuki-firmware-main/movement-sequences.h` | `firmware/movement-sequences.h` |
| `Hardware/yuki-firmware-main_remote/*` | same three files (AP-only variant) |
| `Hardware/debugging-firmware/sesame-motor-tester/` | `firmware/debugging-firmware/` |
| `Hardware/captive-portal-test.html` | `firmware/captive-portal.h` (page markup) |

**What I changed:**

- **Different servo drive path.** Upstream drives the 8 servos directly from GPIO via
  `ESP32Servo`. Yuki drives them through a **PCA9685** 16-channel PWM board
  (`Adafruit_PWMServoDriver`, I²C on pins 21/22), with explicit pulse limits and a
  `servoHome[]` table for per-servo home calibration. This is the change that ripples
  through every firmware file.
- **Removed the OLED face.** Upstream renders animated facial expressions on a 128×64
  SSD1306. Yuki has no display, so the face state machine and `face-bitmaps.h` are gone.
- **Remapped the servo channel order** in `movement-sequences.h` to match my wiring, and
  retuned the pose keyframes and timings for my servos. The set of pose routines
  (`runWalkPose`, `runDancePose`, …) follows upstream.
- **Credentials out of source.** Upstream defines the SSID/password inline in the `.ino`;
  Yuki reads them from a gitignored `secrets.h` (template: `secrets.example.h`).
- **Trimmed the HTTP surface.** Kept `/cmd`, `/getSettings` and `/setSettings`; replaced
  upstream's `/api/status` with a simpler `/status` and dropped `/api/command`.
- **Rebranded** the captive-portal page, and set the mDNS hostname to `yuki.local`.

**What I built myself:** the entire `Yuki-companion-app/` — the LLM-driven natural-language
layer, personality prompt, voice input/TTS, and the HTTP client that drives the robot. This
is original work and is not derived from Sesame Robot.

Not carried over from upstream: Sesame Studio (the animation composer), the Rust simulator,
the OLED face system, and the distro-board hardware designs. If you want those, or a more
capable and better-supported quadruped platform generally, **go use
[Sesame Robot](https://github.com/dorianborian/sesame-robot)** — it is the more complete
project and this one stands on its shoulders.

## License

Licensed under the [Apache License 2.0](LICENSE) — the same license as the upstream Sesame
Robot project it derives from. Third-party attribution is recorded in [NOTICE](NOTICE), and
modified files carry notices describing the changes, as Apache-2.0 §4 requires.
