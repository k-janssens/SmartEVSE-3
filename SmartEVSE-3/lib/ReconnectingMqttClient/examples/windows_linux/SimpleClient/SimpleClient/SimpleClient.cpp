#define MQTT_DEBUGPRINT
#include <ReconnectingMqttClient.h>

uint32_t receive_cnt = 0;

void receive_callback(const char *topic, const uint8_t *payload, uint16_t len, void *) {
  printf("Received topic: %s, message: %.*s\n", topic, len, payload);
  receive_cnt++;
}

int main() {
  // Test publishing of a retained message
  uint8_t ip[] = { 127,0,0,1 };
  ReconnectingMqttClient client(ip, 1883, "simpleclient");
  client.set_receive_callback(receive_callback, NULL);
  bool ok = client.publish("hellotopic", (uint8_t*) "hihello", 7, true, 1);
  printf(ok ? "Publish succeeded.\n" : "Publish failed.\n");

  // Subscribe and read a few published messages, then unsubscribe
  client.subscribe("hellotopic", 1);
  while (client.is_connected() && receive_cnt<2) client.update();
  client.unsubscribe();

  // Subscribe and read a few messages again, then stop the client
  client.subscribe("hellotopic");
  while (client.is_connected() && receive_cnt<4) client.update();
  client.stop();
  return 0;
}

