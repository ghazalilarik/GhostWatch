#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi Configuration
const char* primarySSID = "Network_"; // Base SSID that will change with a random suffix
const char* primaryPassword = "Your_WiFi_Password"; // Replace with your Wi-Fi password
ESP8266WebServer server(80); // Web server on port 80

// Device Fingerprinting
const String knownDevices[] = {"AA:BB:CC:DD:EE:FF", "11:22:33:44:55:66"}; // Replace with known MAC addresses
volatile int unauthorizedDevices = 0;

// SSID Cycling
unsigned long previousMillis = 0;
const long interval = 30000; // Change SSID every 30 seconds

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi initially
  cycleSSID();
  
  // Set up Web Server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started!");

  // Enable Promiscuous Mode for Intrusion Detection
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(promiscuousCallback);
}

void cycleSSID() {
  String newSSID = primarySSID + String(random(1000, 9999)); // Generate a random SSID suffix
  WiFi.softAP(newSSID.c_str(), primaryPassword);
  Serial.println("New SSID: " + newSSID);
}

void promiscuousCallback(uint8_t* buf, uint16_t len) {
  String mac = String(buf[10], HEX) + ":" + String(buf[11], HEX) + ":" + String(buf[12], HEX) +
               ":" + String(buf[13], HEX) + ":" + String(buf[14], HEX) + ":" + String(buf[15], HEX);

  bool isKnownDevice = false;
  for (String device : knownDevices) {
    if (mac.equalsIgnoreCase(device)) {
      isKnownDevice = true;
      break;
    }
  }

  if (!isKnownDevice) {
    unauthorizedDevices++;
    Serial.println("Unauthorized device detected: " + mac);
  }
}

void handleRoot() {
  String html = "<html><head><title>Wi-Fi Cloak & Intrusion Monitor</title></head><body>";
  html += "<h1>ESP8266 'Ghost' Wi-Fi & Intrusion Monitor</h1>";
  html += "<p>Unauthorized Devices Detected: " + String(unauthorizedDevices) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void loop() {
  server.handleClient();

  // Check if it's time to cycle SSID
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    cycleSSID(); // Change SSID periodically
  }
  
  delay(1000); // Delay for stability
}
