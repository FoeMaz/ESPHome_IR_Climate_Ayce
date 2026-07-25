# ESPHome IR Climate Component for Ayce Air Conditioners ❄️
This is an extension to the ESP Home IR Remote Climate for Ayce (and maybe generic) ACs
Dieses Repository enthält eine **ESPHome**-Komponente zur Steuerung von **Ayce Klimageräten** (z. B. vertrieben über Jumbo / Coop) über einen Infrarot (IR)-Sender. Damit kannst du deine Ayce-Klimaanlage nahtlos in **Home Assistant** einbinden und automatisieren.

---

## 📑 Inhaltsverzeichnis

- [Features](#-features)
- [Voraussetzungen & Hardware](#-voraussetzungen--hardware)
- [Einbindung in ESPHome](#-einbindung-in-esphome)
- [Konfigurationsbeispiel (YAML)](#-konfigurationsbeispiel-yaml)
---

## ✨ Features

- 🌡️ **Temperatursteuerung:** Zieltemperatur präzise über Home Assistant einstellen.
- 🔄 **Betriebsmodi:** Unterstützt Kühlen (*Cool*), Entfeuchten (*Dry*), Nur-Ventilator (*Fan Only*) und Aus (*Off*).
- 💨 **Lüfterstufen (Fan Speed):** Steuerung der Ventilatorgeschwindigkeit (Low, Medium, High).
- ↕️ **Lamellen-Steuerung (Swing):** Ein-/Ausschalten der vertikalen Oszillation.
- 🏠 **Home Assistant Ready:** Automatische Erkennung als Standard-Climate-Entität in HA.

---

## 📦 Voraussetzungen & Hardware

### Hardware
1. **Mikrocontroller:** ESP32 oder ESP8266 (z. B. NodeMCU, ESP32 D1 Mini).
2. **IR-Transmitter (Sender):** 
3. **Optional – Temperatursensor:** Z. B. BME280, DHT22 oder DS18B20 zur Rückmeldung der aktuellen Raumtemperatur an Home Assistant.

### Software
- Installiertes [ESPHome](https://esphome.io/) (als Home Assistant Add-on oder Standalone CLI).

---

## 🚀 Einbindung in ESPHome

Füge dieses Repository als `external_component` in deine ESPHome-YAML-Konfigurationsdatei ein.

### Konfigurationsbeispiel (YAML)

Siehe Ayce.yaml
