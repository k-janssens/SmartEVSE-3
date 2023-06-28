#include <ReconnectingMqttClient.h>

// WiFi network to connect to
const char* ssid     = "MyNetworkSSID";
const char* password = "MyNetworkPassword";

void receive_callback(const char *topic, const uint8_t *payload, uint16_t len, void *) {
  Serial.print("Received topic: "); Serial.print(topic); 
  Serial.print(", message: "); Serial.write(payload, len); 
  Serial.println();
}

uint8_t ip[] = { 192,168,1,71 }; // Broker address
ReconnectingMqttClient client(ip, 1883, "reconnectingclient");

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("Now listening at IP %s\n", WiFi.localIP().toString().c_str());

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

