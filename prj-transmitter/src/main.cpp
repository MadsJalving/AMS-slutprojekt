// ===============================
// AUTHOR       : Mads Jalving & Peter Schultz-Johansen
// CREATE DATE  : 26/04/2023
// PURPOSE      : SWAMS Slutprojekt
// SPECIAL NOTES: Transmitter modul
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

#include <util/delay.h>

RF24 radio(PB1, PB2);

void initTransmitter();

const byte address[6] = "00001";
void *buffer = malloc(sizeof(char));

int main()
{
    Serial.begin(115200);

    Serial.write("Hello from Transmitter\n");

    initTransmitter();

    while(1)
    {
        char newBuf = Serial.read();
        buffer = &newBuf;

        radio.write(&buffer, sizeof(buffer));

        buffer = NULL;
    
    }
    return 0;
}

void initTransmitter()
{
    radio.begin(); 
    radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.stopListening();              //This sets the module as transmitter 
}

