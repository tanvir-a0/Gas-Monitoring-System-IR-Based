#include <IRremote.h>

int IR_RECEIVE_PIN = 2;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(115200);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Raw received value: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.print("Protocol used: ");
    Serial.println(IrReceiver.decodedIRData.protocol);
    IrReceiver.resume(); // Prepare for the next value
    if (IrReceiver.decodedIRData.protocol == SAMSUNG) {
      Serial.println("Samsung protocol detected.");
      Serial.println(IrReceiver.decodedIRData.address, HEX);
      Serial.println(IrReceiver.decodedIRData.command, HEX);
      Serial.print("mq135 (0 to 255): ");
      Serial.print(IrReceiver.decodedIRData.address, DEC);
      Serial.print(" mq6 (0 to 255): ");
      Serial.print(IrReceiver.decodedIRData.command, DEC);
      Serial.println();
    }
  }
}