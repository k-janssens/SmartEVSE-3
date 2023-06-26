# ReconnectingMqttClient
Portable simple header-only C++ MQTT client library for Windows, Linux, Arduino, Raspberry, ESP8266, ESP32++

## WHY another MQTT library?
The list of C++ alternatives is not long, and none of them cover the range from Arduino compatible devices to Windows and Linux based devices. This library does.
Also, this library is very small and header-only, only a few hundred lines of code. Alternatives like Paho C/C++ are hundreds of files and tens of thousands of lines of code, and may give some more grief if not having the right environment when building. On Arduino, the excellent PubSubClient library is easy to use, but cannot be used on Windows or Linux based platforms.

## Description
This is a simple and portable C++ header-only library for creating MQTT clients. It supports publish and subscribe, retain, QoS level 0 and 1, text or binary payloads.

It is aimed at being used on multiple platforms. It can be built on:
* Multiple cards supported by the Arduino development environment, including Arduino Uno/Nano/Mega, ESP8266, ESP32 and others.
* Windows, with project files included for examples for Visual Studio 2017 or later.
* Linux, with Makefiles included for examples.

This library depends on the [PJON](https://github.com/gioblu/PJON) library for portability.

Example client on Windows or Linux based platforms:

```cpp
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

  // Subscribe and read a few published messages, then unsubscribe and stop
  client.subscribe("hellotopic", 1);
  while (client.is_connected() && receive_cnt<5) client.update();
  return 0;
}
```

On Arduino the same structure is used except for moving the calls into setup() and loop().
