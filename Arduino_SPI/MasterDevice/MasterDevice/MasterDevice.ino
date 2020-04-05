//SPI Master Device
//We need to import SPI.h library first 
#include <SPI.h>

//Our Slave Selection pin
#define SlaveSelection  10

int count = 0;

void setup()
{
  //Set SlaveSelection pin as output.
  pinMode(SlaveSelection, OUTPUT);
  //and Make it HIGH to prevent to start communication right away
  digitalWrite(SlaveSelection, HIGH);
  //Start the SPI communication.
  SPI.begin();
}
 
void loop()
{

    for(count=0; count<255; count++){
      sendSerialData(count , SlaveSelection);
      delay(2000);
    }
    delay(500);
}
 
void sendSerialData(char data, int SlaveSelection)
{
  //Enable slave arduino with setting the SlaveSelection pin to 0Volt
  digitalWrite(SlaveSelection, LOW);
  // Wait for a moment 
  delay(10);
  //We sent the data here and wait for the response from device
  char receivedValue = SPI.transfer(data);
  //And then write the answer to the serial port
  Serial.println(receivedValue);
  //Disable slave arduino with setting the SlaveSelection pin to 5Volt
  digitalWrite(SlaveSelection, HIGH);
}
