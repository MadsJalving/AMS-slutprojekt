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


#include <RF24.h>
#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>
#include <string.h>
#include <SPI.h>
#include <printf.h>
#include "RF24.h"

#include <util/delay.h>

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);

void initTransmitter();
void sendString(char key);

const byte slaveAddress[6] = "00002";
char buffer;

int main()
{
    init();
    Serial.begin(9600);

    while(!Serial)
    {}

    printf_begin();

    Serial.print(F("Hello from transmitter\n"));

    initTransmitter();

    radio.printPrettyDetails();

    char testString[] = "Hello from transmitter";

    for(;;)
    {
        radio.write(&testString, sizeof(testString));
        
        Serial.println(testString);

        _delay_ms(1000);
    
        // if (Serial.available() > 0)
        // {
        //     // char key = Serial.read();
        //     // if (key == 'w' || key == 'a' || key == 's' || key == 'd')
        //     // {
        //     //     sendString(key);
        //     //     Serial.print("Send key: ");
        //     //     Serial.print(key);
        //     //     Serial.print('\n');
        //     // }
        // }
    }
    return 0;
}

void initTransmitter()
{
    // if(!radio.begin())
    // {
    //     Serial.print(F("    Radio hardware not responding!\n"));
    //     while(1){}
    // }
    radio.begin();
    radio.openWritingPipe(slaveAddress);    //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);          //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();                  //This sets the module as transmitter 
    radio.setChannel(76);
}

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
    
    bool x = radio.write(&buf, sizeof(buf));
    _delay_ms(10); // Radio needs ~10 ms for message to be sent properly

    if(x) // send the key over radio
    {
        Serial.print("Send successful\n");
    }
    else
    {
        Serial.print("  Send not successful!\n");
    }
    prevKey = buf[0];              // update the previous key
}