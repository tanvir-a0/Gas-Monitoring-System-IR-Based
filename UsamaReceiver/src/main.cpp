#include <IRremote.h>

int IR_RECEIVE_PIN = 2;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(115200);
}

void loop() {
  if (IrReceiver.decode()) {
    //Serial.print("Raw received value: ");
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    //Serial.print("Protocol used: ");
    //Serial.println(IrReceiver.decodedIRData.protocol);
    IrReceiver.resume(); // Prepare for the next value
    if (IrReceiver.decodedIRData.protocol == SAMSUNG) {
      Serial.println("Samsung protocol detected.");
      Serial.println(IrReceiver.decodedIRData.address, HEX);
      //now we can modify the data like this:
      //the data will have a serial and data
      //the data will be stored in address and value will be stored in command
      int sensor_serial = IrReceiver.decodedIRData.address;
      int sensor_data = IrReceiver.decodedIRData.command;

      Serial.print("Sensor serial: ");
      Serial.println(sensor_serial, DEC);
      Serial.print("Sensor data: ");
      Serial.println(sensor_data, DEC);
    }
  }
}