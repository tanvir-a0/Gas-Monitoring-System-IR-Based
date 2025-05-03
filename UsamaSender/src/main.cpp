#include <IRremote.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; // I2C

int IR_SEND_PIN = 3;

const int numberOfSensors = 5;
int sensorData[numberOfSensors];

int Min_Pressure = 30000 ;
int Max_Pressure = 110000 ; //the value in degree celsius
int Min_Temp = -40;
int Max_Temp = 85; //the value in degree celsius

void setup() {
  IrSender.begin(IR_SEND_PIN);
  Serial.begin(115200);

  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
      Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
      Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
      Adafruit_BMP280::FILTER_X16,      /* Filtering. */
      Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  }

void loop() {
  int temperature = bmp.readTemperature();
  int pressure = bmp.readPressure();
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" *C, Pressure = ");
  Serial.print(pressure);
  Serial.print(" Pa");

  int mq135data  = analogRead(A0); // Read the value from the MQ135 sensor
  int mq6data    = analogRead(A1); // Read the value from the MQ6 sensor
  int mq2data    = analogRead(A2); // Read the value from the MQ2 sensor
  sensorData[0] = mq135data >> 2; // Shift the sensor data to fit into the command
  sensorData[1] = mq6data >> 2;   // Shift the sensor data to fit into the command
  sensorData[2] = mq2data >> 2;   // Shift the sensor data to fit into the command
  sensorData[3] = map(temperature, Min_Temp, Max_Temp, 0, 255); // Map temperature to 0-255 range
  sensorData[4] = map(pressure, Min_Pressure, Max_Pressure, 0, 255); // Map pressure to 0-255 range

  for(int i = 0; i < numberOfSensors; i++)
  {
    uint8_t address = 0x07;  // example address
    uint8_t command = 0x45;  // example command

    address = i ;
    command = sensorData[i]; // Shift the sensor data to fit into the command
    
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
