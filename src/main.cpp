#include <Arduino.h>
#include <painlessMesh.h>
#include <string.h>

#include "data.hpp"

void received_callback(const uint32_t &from, const String &msg);

painlessMesh mesh;
String chip_id;
void setup() {
	// Serial.begin(BAUDRATE);
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
    if (msg.equals(":20000022294766936e\n")) {
		String message = ":100000" + String(mesh.getNodeId()) + "64" + "\n";
		mesh.sendBroadcast(message);
	}
}
