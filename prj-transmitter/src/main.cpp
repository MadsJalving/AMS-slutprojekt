// ===============================
// AUTHOR       : Mads Jalving & Peter Schultz-Johansen
// CREATE DATE  : 26/04/2023
// PURPOSE      : SWAMS Slutprojekt
// SPECIAL NOTES: Transmitter modul
// ===============================
// Change History:
//      - 26/04/2023
//          Oprettelse og indledende redigeringer
//      - 02/05/2023
//          Oprettelse af ny transmitter kode, som kan sende w, a, s & d
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
char buffer;

void sendString(char key)
{
    static char prevKey = '\0'; // keep track of the previously sent key
    char buf[2] = {key, '\0'};  // create a string with the current key

    // check if both A and D or both W and S are pressed simultaneously
    if ((prevKey == 'a' && key == 'd') || (prevKey == 'd' && key == 'a') ||
      (prevKey == 'w' && key == 's') || (prevKey == 's' && key == 'w'))
    {
        // send the previous key instead of the current one
        buf[0] = prevKey;
    }
  
    radio.write(buf, sizeof(buf)); // send the key over radio
    prevKey = buf[0];              // update the previous key
}

int main()
{
    init();
    Serial.begin(9600);

    while(!Serial)
    {}

    Serial.print(F("Hello from transmitter\n"));

    initTransmitter();

    for(;;)
    {
        if (Serial.available() > 0)
        {
            char key = Serial.read();
            if (key == 'w' || key == 'a' || key == 's' || key == 'd')
            {
                sendString(key);
                Serial.print("Send key: ");
                Serial.print(key);
                Serial.print('\n');
            }
        }
    }
    return 0;
}

void initTransmitter()
{
    radio.begin(); 
    radio.openWritingPipe(address);   //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);    //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.stopListening();           //This sets the module as transmitter 
}


