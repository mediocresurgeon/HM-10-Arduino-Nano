#include <stdlib.h>
#include <SoftwareSerial.h>

// Pin numbers for Arduino Nano can be found here:
// https://forum.arduino.cc/uploads/short-url/4lT7GD4tgRcDvingrjAzuJjM4fM.pdf
#define TX1  1
#define RX0  0
#define D2   2 /* Hardware Interrupt */
#define D3   3 /* Hardware Interrupt */
#define D4   4
#define D5   5
#define D6   6
#define D7   7
#define D8   8
#define D9   9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define A0  14
#define A1  15
#define A2  16
#define A3  17
#define A4  18
#define A5  19

SoftwareSerial HM10(D4, D5);
bool writeZero = false;
volatile unsigned int changesDetected = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600);
  attachInterrupt(digitalPinToInterrupt(D2), onDetected, FALLING);
}

void loop() {
  char buffer [11];
  if (changesDetected) {
    unsigned int temp = changesDetected;
    changesDetected = 0;
    writeZero = true;
    
    itoa(temp, buffer, 10);
    HM10.write(buffer);
    Serial.println(buffer);
  }
  else if (writeZero) {
    writeZero = false;
    
    HM10.write("0\0");
    Serial.println("0\0");
  }
}

void onDetected() {
  changesDetected++;
}
