#include <WiFiNINA.h>
#include <ThingSpeak.h>

// WiFi settings
char ssid[] = "MM";                   // WiFi network name
char pass[] = "1234567890";           // WiFi password

// ThingSpeak settings
unsigned long channelID = 2249912;    // ThingSpeak channel ID
const char *writeAPIKey = "RJKPE27QCV40MNZM";  // ThingSpeak write API Key

// LDR sensor settings
int ldrPin = A0;                      // Analog pin where LDR is connected

WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module communication failed!");
    while (true);  // Stuck here, something is really wrong
  }

  // Try to connect to WiFi
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }

  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak communication
  ThingSpeak.begin(client);
}

void loop() {
  // Read light intensity from LDR sensor
  int ldrValue = analogRead(ldrPin);

  // Display light intensity
  Serial.print("Light Intensity: ");
  Serial.println(ldrValue);

  // Set the value for ThingSpeak field
  ThingSpeak.setField(1, ldrValue);

  // Send data to ThingSpeak channel
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (response == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error: " + String(response));
  }

  delay(5000); // Wait 20 seconds before the next update
}
