#include <Arduino.h>
#include <painlessMesh.h>
#include <string.h>

#include "data.hpp"

void received_callback(const uint32_t &from, const String &msg);

painlessMesh mesh;
String chip_id;
void setup() {
	Serial.begin(BAUDRATE);
    chip_id = String(ESP.getChipId());

	//mesh
	// mesh.setDebugMsgTypes(ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE);   // all types on

	mesh.init(ssid, password, PORT);
	mesh.setContainsRoot(true);
	mesh.onReceive(&received_callback);
}

void loop() {
	mesh.update();
}

void received_callback(const uint32_t &from, const String &msg) {
    mesh.sendBroadcast(chip_id + String('\t') + msg);
}
