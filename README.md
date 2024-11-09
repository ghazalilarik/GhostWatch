# GhostWatch - ESP8266 'Ghost' Wi-Fi (Network Cloaking) + Intrusion Detection

![Meme](https://i.imgflip.com/2wifvo.jpg)

*“When your ESP8266 goes stealth mode and catches Wi-Fi intruders off guard.”*

## Overview
**GhostGuard** is an ESP8266 project that combines Wi-Fi network cloaking with intrusion detection. It periodically changes the SSID to keep the network hidden from potential intruders while logging any unauthorized devices attempting to connect, providing a secure and stealthy network experience.

---

## Disclaimer
This project is intended for educational and ethical use only. Unauthorized network monitoring and SSID cloaking may be restricted in some regions. Use responsibly and with permission. The authors are not responsible for any misuse or legal consequences.

---

## Features
- **Network Cloaking**: Periodically changes the Wi-Fi SSID to prevent tracking by potential attackers.
- **Intrusion Detection**: Logs unauthorized device connections based on MAC address filtering.
- **Web Interface**: Real-time logs of unauthorized devices attempting to connect to the network.

## Installation

### Requirements
- **ESP8266** (e.g., NodeMCU)
- **Arduino IDE** with ESP8266 library
- **Wi-Fi credentials** (SSID prefix and password)

### Setup
1. **Install ESP8266 Board in Arduino IDE**:
   - Go to **File > Preferences**.
   - Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` under **Additional Board Manager URLs**.
   - Go to **Tools > Board > Board Manager**, search for **ESP8266**, and install.

2. **Upload the Code**:
   - Replace `primaryPassword` with your Wi-Fi password.
   - Add known device MAC addresses in `knownDevices[]` for authorized access monitoring.
   - Select the **ESP8266 board** and **COM port** in **Tools**, then upload the code.

3. **Access the Web Interface**:
   - Connect a device to the ESP8266’s network.
   - Enter the ESP8266’s IP address (usually `192.168.4.1`) in a browser to access the web interface.

---

## How to Use
1. **Network Cloaking**:
   - The ESP8266 periodically cycles the SSID every 30 seconds (customizable in code) to make it harder to track the network.
   - Each new SSID is a combination of a base name and a random suffix.

2. **Intrusion Detection**:
   - Unauthorized devices attempting to connect are identified based on MAC address.
   - If an unknown MAC address is detected, it logs the attempt and updates the count on the web interface.

3. **Web Interface**:
   - Use the web interface to view the count of unauthorized device attempts and monitor network access in real time.

## Advantages
- Provides basic network cloaking by regularly changing SSID.
- Detects and logs unauthorized access attempts, enhancing security.
- Lightweight, easy to monitor through a web interface.

## Disadvantages
- Limited to detecting unauthorized devices by MAC address filtering.
- Network cloaking may cause reconnect issues for authorized devices.
- May not prevent attacks but provides awareness and cloaking for enhanced security.

## License
This project is open-source and available under the MIT License.
