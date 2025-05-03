#include <IRremote.h>

int IR_SEND_PIN = 3;

void setup() {
  IrSender.begin(IR_SEND_PIN);
  Serial.begin(115200);
}

void loop() {
  int mq135data  = analogRead(A0); // Read the value from the MQ135 sensor
  int mq6data    = analogRead(A1); // Read the value from the MQ6 sensor
  uint8_t address = 0x07;  // example address
  uint8_t command = 0x45;  // example command

  address = mq135data >> 2;
  command = mq6data >> 2; // Shift the sensor data to fit into the command
  
  Serial.print("Sending Samsung IR: ");
  Serial.print("Address = 0x");
  Serial.print(address, HEX);
  Serial.print(", Command = 0x");
  Serial.println(command, HEX);

  IrSender.sendSamsung(address, command, 0); // send once
  delay(2000);
}
