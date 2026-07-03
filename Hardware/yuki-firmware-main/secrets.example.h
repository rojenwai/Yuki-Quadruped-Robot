#pragma once

// -------- WiFi credentials template --------
// Copy this file to secrets.h (same folder) and fill in your own values.
// secrets.h is gitignored so your credentials are never committed.

// Station mode: the network/hotspot Yuki joins for internet access
#define WIFI_SSID "your-wifi-name"
#define WIFI_PASS "your-wifi-password"

// Access Point mode: Yuki's own network you connect to for control
// (AP_PASS must be at least 8 characters)
#define AP_SSID "Yuki's-Controller"
#define AP_PASS "change-me"
