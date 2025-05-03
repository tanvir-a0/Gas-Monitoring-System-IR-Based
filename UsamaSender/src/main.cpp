#include <IRremote.h>

int IR_SEND_PIN = 3;

const int numberOfSensors = 4;
int sensorData[numberOfSensors];

void setup() {
  IrSender.begin(IR_SEND_PIN);
  Serial.begin(115200);
}

void loop() {
  int mq135data  = analogRead(A0); // Read the value from the MQ135 sensor
  int mq6data    = analogRead(A1); // Read the value from the MQ6 sensor
  int mq2data    = analogRead(A2); // Read the value from the MQ2 sensor
  sensorData[0] = mq135data;
  sensorData[1] = mq6data;
  sensorData[2] = mq2data;

  for(int i = 0; i < numberOfSensors; i++)
  {
    uint8_t address = 0x07;  // example address
    uint8_t command = 0x45;  // example command

    address = i ;
    command = sensorData[i] >> 2; // Shift the sensor data to fit into the command
    
    Serial.print("Sending Samsung IR: ");
    Serial.print("Address = 0x");
    Serial.print(address, HEX);
    Serial.print(", Command = 0x");
    Serial.println(command, HEX);
    IrSender.sendSamsung(address, command, 0); // send once
    delay(100); // Delay between sends to avoid flooding the receiver
  }
  delay(2000);
}
