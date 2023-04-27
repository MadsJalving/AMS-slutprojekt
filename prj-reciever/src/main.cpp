// ===============================
// AUTHOR       : Mads Jalving & Peter Schultz-Johansen
// CREATE DATE  : 26/04/2023
// PURPOSE      : SWAMS Slutprojekt
// SPECIAL NOTES: Reciever modul
// ===============================
// Change History:
//      - 26/04/2023
//          Oprettelse og indledende redigeringer
//==================================

#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>
#include <string.h>
#include <Servo.h>

#include <util/delay.h>

#include "motorControl.hpp"

RF24 radio(PB1, PB2);

void initReciever();

const byte address[6] = "00001";
void *buffer = malloc(sizeof(char));

int main()
{
  Serial.begin(115200);

  Serial.write("Hello from Reciever\n");

  initReciever();

  motorSetup();

  while(1)
  { 
    radio.read(buffer, sizeof(buffer));

    switch (buffer)
    {
      case 'w':
        // forhøj fart-variabel
        break;

      case 'a':
        // vinkel mod venstre
        break;

      case 's':
        // sænk fart-variabel
        break;

      case 'd':
        // vinkel mod højre
        break;

      case 'x':
        // Her skal den stoppe
        break;
        
      default:
        break;
    }
  }
  return 0;
}

void initReciever()
{
  radio.begin(); 
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data 
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
  radio.startListening();              //This sets the module as reciever
}

void motorAdjust(byte speed)
{

}