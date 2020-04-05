//Slave device of the SPI communication

#include <SPI.h>
char i = 0;

#define SlaveSelection  10

void setup()
{
  //Start the Serial Communication
  Serial.begin(9600);   
    
  // initialize SPI :
  pinMode(SlaveSelection , INPUT); // Set SlaveSelection as input
  pinMode(13,OUTPUT);   // Set clk as output
  pinMode(11,OUTPUT);   // Set MOSI as output
  pinMode(12,INPUT);    // Set MISO as input
  
  // SPCR - SPI Control Register
  // According to struct table we enable the SPI and Interface
  SPCR  |= 0b11000000;
  // SPSR - SPI Status Register
  SPSR  |= 0x00;
}  
 
void loop()
{
  delay(1000);
}

//SPI Interrupt function 
ISR(SPI_STC_vect)
{
    //Here we read the SPI lines
    //This line will check data for every ASCII codes for 8-bit received data
    //SPDR -> SPI Data Read bit
    SPDR = i;
    i ++;
    if ( i > 255) 
      i = 0;
    while(!(SPSR & (1 << SPIF)));
    //Load the received data to the variable
    char received = SPDR;
    //And send it to the serial communication bus
    Serial.println(received);
}
