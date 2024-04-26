// Libraries
#include <SoftwareSerial.h>
#include <Wire.h>

// Pin definitions for various sensors and components
#define sensorPower 7
#define moistureSensorPin A0
#define pHSensorPin A1
#define RE 8
#define DE 7

unsigned long int avgValue;  
float b;
int buf[10], temp;
byte values[11];

// Modbus RTU requests for reading NPK values
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

SoftwareSerial mod(2, 3); // Setup software serial for Modbus communication

void setup() {
  pinMode(sensorPower, OUTPUT); // Setup the sensor power pin as output
  

  digitalWrite(sensorPower, LOW); // Initially turn off sensor power
  
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  mod.begin(9600); // Start modbus communication at 9600 baud rate
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  delay(500);
}

void loop() {
  
  // NPK Readings
  byte nitrogenVal, phosphorusVal, potassiumVal;
  
  // Read nutrient values from sensors
  nitrogenVal = nitrogen();
  delay(250);
  phosphorusVal = phosphorous();
  delay(250);
  potassiumVal = potassium();
  delay(250);
  
  // Print all sensor values to serial
  Serial.print(readSoilMoisture());
  Serial.print(",");
  Serial.print(readPhValue(), 2);
  Serial.print(",");
  Serial.print(nitrogenVal);
  Serial.print(",");
  Serial.print(phosphorusVal);
  Serial.print(",");
  Serial.println(potassiumVal);

  delay(4000); // Delay before next reading
}

// Function to read soil moisture value
int readSoilMoisture() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  int val = analogRead(moistureSensorPin); // Read analog value from sensor
  digitalWrite(sensorPower, LOW);
  return val;
}

// Function to read pH value from sensor
float readPhValue() {
  // Take 10 readings
  for (int i = 0; i < 10; i++) { 
    buf[i] = analogRead(pHSensorPin);
    delay(10);
  }
  
  // Sort the analogue from small to large
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];
  float phValue = (float)avgValue * 5.0 / 1024 / 6; // Convert the analogue into millivolt


  phValue = 3.5 * phValue; // Convert the millivolt into pH value

  return phValue;
}

// Function to read nitrogen levels using Modbus protocol
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
  }
  return values[4];
}

// Function to read phosphorus levels using Modbus protocol
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
  }
  return values[4];
}

// Function to read potassium levels using Modbus protocol
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
  }
  return values[4];
}
