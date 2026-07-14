# Yuki Companion App

A voice/text natural-language interface for the **Yuki** quadruped robot. It turns what
you say into a personality-driven response plus a robot command, speaks the response, and
sends the command to Yuki's ESP32 over WiFi.

```
You ──speech/text──▶ companion app ──LLM──▶ {command, response}
                          │                      │
                     speak response        HTTP GET /cmd?... ──▶ ESP32 (servos)
```

## Requirements

- Python 3.8+
- Yuki's ESP32 powered on and reachable on your network (see [the firmware](../Hardware/yuki-firmware-main/))
- One AI backend:
  - **Google Gemini** API key from [aistudio.google.com](https://aistudio.google.com/app/apikey), or
  - a **local OpenAI-compatible LLM** (Ollama / LM Studio)

## Installation

```powershell
pip install -r requirements.txt
```

> On Windows, `PyAudio` (needed for the microphone) sometimes needs a prebuilt wheel —
> `pip install pipwin; pipwin install pyaudio` is the usual fallback.

## Configuration

Copy `.env.example` to `.env` and edit it (the app loads `.env` automatically), or set the
same names as environment variables.

| Variable | Default | Purpose |
|---|---|---|
| `YUKI_ROBOT_IP` | `yuki.local` | Robot IP / mDNS host, or `mock` to run without hardware |
| `YUKI_LOCAL` | `false` | `false` = Gemini, `true` = local LLM |
| `GEMINI_API_KEY` | – | Required when `YUKI_LOCAL=false` |
| `LOCAL_LLM_URL` | `http://localhost:11434/v1` | OpenAI-compatible endpoint |
| `LOCAL_LLM_MODEL` | `llama3` | Local model name |
| `VOICE_ENABLED` | `true` | Enable mic + TTS |
| `TTS_ENGINE` | `pyttsx3` | `pyttsx3` (offline) or `gemini` (cloud) |
| `WAKE_WORD` | `hey yuki` | Wake phrase |
| `WAKE_WORD_MODE` | `false` | Listen for the wake word |
| `MOVE_DURATION` | `0` | Seconds before auto-stopping locomotion (`0` = until "stop") |
| `DEBUG` | `false` | Print raw AI interpretations |

## Usage

```powershell
python yuki_companion.py
```

At the prompt you can type or speak naturally ("dance", "walk forward", "how are you?").
Built-in keywords: `voice`, `wakeword`, `tts`, `status`, `help`, `quit`/`exit`.

To try it with no robot attached, set `YUKI_ROBOT_IP=mock`.

## Commands

`forward`, `backward`, `left`, `right`, `rest`, `swim`, `dance`, `wave`, `point`, `stand`,
`cute`, `pushup`, `freaky`, `bow`, `worm`, `shake`, `shrug`, `dead`, `crab`, `stop`.

The AI only emits a command for a direct order; otherwise it just chats. Greetings
auto-trigger `wave`.

## How it talks to the robot

The ESP32 exposes a simple HTTP GET API (served alongside its captive-portal web UI):

| Request | Effect |
|---|---|
| `GET /cmd?go=forward\|backward\|left\|right` | Continuous locomotion until stopped |
| `GET /cmd?pose=<name>` | Run a one-shot pose (dance, wave, …) |
| `GET /cmd?stop=1` | Stop |
| `GET /cmd?motor=<1-8>&value=<0-180>` | Drive a single servo (tuning) |
| `GET /status` | JSON: `currentCommand`, `networkConnected`, `sta`, `ap` |
| `GET /getSettings` / `GET /setSettings?...` | Read/update frame delay, walk cycles, etc. |

Locomotion (`go=...`) runs continuously on the robot until a `stop`. Set `MOVE_DURATION`
so a single "walk forward" automatically stops after N seconds.

## Components

- **`VoiceInterface`** — speech recognition (Google Speech API) and TTS (pyttsx3 or Gemini),
  with optional wake-word listening.
- **`YukiRobotController`** — HTTP client for the ESP32; command→URL mapping, reachability
  check via `/status`, and a shared `requests.Session`. Supports `mock` mode.
- **`GeminiInterface` / `LocalLLMInterface`** — turn user input into
  `{command, response, reasoning}` JSON using Yuki's personality prompt.
- **`YukiCompanionApp`** — orchestrates the above and runs the interactive CLI loop.

## Finding the robot

- If mDNS works on your network, just use `yuki.local`.
- Otherwise connect Yuki via USB, open the serial monitor at **115200 baud**, and read the
  `STA IP (internet): X.X.X.X` line.
- Quick check: `curl http://yuki.local/status` (or `http://<ip>/status`).

## Troubleshooting

- **Can't connect** — confirm same network/subnet, try the IP instead of `yuki.local`, and
  test `curl http://<ip>/status`.
- **Microphone errors** — ensure `PyAudio` installed (see Installation note).
- **Gemini TTS silent** — needs a valid `GEMINI_API_KEY` and `pygame`; it falls back to
  pyttsx3 on error.
- **Local LLM returns non-JSON** — use an instruct model that honors JSON output; the app
  strips markdown fences and retries without `response_format` if the backend rejects it.
