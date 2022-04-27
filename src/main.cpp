#include <Arduino.h>
#include <painlessMesh.h>
#include <string.h>

#include "data.hpp"

void received_callback(const uint32_t &from, const String &msg);

painlessMesh mesh;
void setup() {
	Serial.begin(BAUDRATE);

	//mesh
	// mesh.setDebugMsgTypes(ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE);   // all types on

	mesh.init(ssid, password, PORT);
	mesh.setContainsRoot(true);
	mesh.onReceive(&received_callback);

    //message_offset
    for (int i = 0; i < OFFSET_SIZE; i++)
        message_offset += String(':');
}

void loop() {
	mesh.update();
}

void received_callback(const uint32_t &from, const String &msg) {
    mesh.sendBroadcast(String(ESP.getChipId()) + String('\t') + msg);
}
