#include <ReconnectingMqttClient.h>

// Ethernet configuration for this device, MAC must be unique!
byte mac[] = {0xDE, 0x11, 0x4E, 0x1F, 0xFE, 0xE1};

void receive_callback(const char *topic, const uint8_t *payload, uint16_t len, void *) {
  Serial.print("Received topic: "); Serial.print(topic); 
  Serial.print(", message: "); Serial.write(payload, len); 
  Serial.println();
}

uint8_t ip[] = { 192,168,1,71 };
ReconnectingMqttClient client(ip, 1883, "reconnectingclient");

void setup() {
  Serial.begin(115200);
  while (Ethernet.begin(mac) == 0) delay(5000); // Wait for DHCP response

  // Test publishing of a retained message
  client.set_receive_callback(receive_callback, NULL);
  bool ok = client.publish("hellotopic", (uint8_t*) "hihello", 7, true, 1);
  Serial.println(ok ? "Publish succeeded.\n" : "publish failed.\n");

  // Subscribe
  client.subscribe("hellotopic", 1);
}

void loop() {
  client.update();
}

