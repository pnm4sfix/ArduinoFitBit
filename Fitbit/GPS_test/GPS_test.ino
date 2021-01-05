#include <TinyGPS.h>
#include <Arduino.h>
#include "wiring_private.h"
//#include <UART.h>
TinyGPS gps;


//Uart mySerial(digitalPinToPinName(4), digitalPinToPinName(3), NC, NC);
Uart mySerial (&sercom0, 4, 3, SERCOM_RX_PAD_1, UART_TX_PAD_0);
// Attach the interrupt handler to the SERCOM
void SERCOM0_Handler()
{
    mySerial.IrqHandler();
}

void setup() {
  // put your setup code here, to run once:
  //Uart mySerial(digitalPinToPinName(4), digitalPinToPinName(3), NC, NC);
  Serial.begin(9600);
  pinPeripheral(4, PIO_SERCOM); //Assign RX function to pin 0
  pinPeripheral(3, PIO_SERCOM);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  gps.encode(mySerial.read());
  Serial.print(gps.location.lat());
 
}
