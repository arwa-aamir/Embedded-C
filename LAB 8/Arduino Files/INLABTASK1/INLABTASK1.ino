// I2C Digital Potentiometer interfacing with Arduino
// Controls AD5241 digital potentiometer via I2C/TWI
#include <Wire.h>
void setup() 
{
  Wire.begin(); // join i2c bus (address optional for master)
}
byte val = 0;
void loop() 
{
  Wire.beginTransmission(44); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x00)); // sends instruction byte
  Wire.write(val); // sends potentiometer value byte
  Wire.endTransmission(); // stop transmitting
  val++; // increment value
  if (val == 255) 
  { // if reached max value 255
    val = 0; // start over from lowest value
  }
delay(750);
}
