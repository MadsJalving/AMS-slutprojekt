// ===============================
// AUTHOR       : Mads Jalving & Peter Schultz-Johansen
// CREATE DATE  : 26/04/2023
// PURPOSE      : SWAMS Slutprojekt
// SPECIAL NOTES: Reciever modul
// ===============================
// Change History:
//      - 26/04/2023
//          Oprettelse og indledende redigeringer
//      - 02/05/2023
//          Oprettelse af ny reciever kode, som modtager input fra transmitter.
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

void initReceiver();

const byte address[6] = "00001";
char buffer;

int main()
{
    Serial.begin(115200);

    Serial.write("Hello from Receiver\n");

    initReceiver();

    while(1)
    { 
        if (radio.available()) {
            radio.read(&buffer, sizeof(buffer));

            switch (buffer)
            {
              case 'w':
                Serial.println("Key W is pressed");
                break;

              case 'a':
                Serial.println("Key A is pressed");
                break;

              case 's':
                Serial.println("Key S is pressed");
                break;

              case 'd':
                Serial.println("Key D is pressed");
                break;
              
              default:
                break;
            }
        }
    }
    return 0;
}

void initReceiver()
{
    radio.begin(); 
    radio.openReadingPipe(0, address); //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);     //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.startListening();            //This sets the module as receiver
}