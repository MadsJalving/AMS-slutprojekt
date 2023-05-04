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

#include <util/delay.h>

RF24 radio(PB1, PB2);

void initTransmitter();
void sendString(char key);

const byte pipe[6] = "00001";
char buffer;

int main()
{
    init();
    Serial.begin(9600);
    SPI.begin();

    while(!Serial)
    {}

    Serial.print(F("Hello from transmitter\n"));

    initTransmitter();

    char testString[] = "Hello from transmitter";

    bool x;

    for(;;)
    {
        x = radio.write(testString, sizeof(testString));
        if (x)
            {
                Serial.print("  Send successful!\n");
            }
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
    if(!radio.begin())
    {
        Serial.print(F("    Radio hardware not responding!\n"));
        while(1){}
    }
    radio.openWritingPipe(pipe);   //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);    //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.stopListening();            //This sets the module as transmitter 
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
    
    bool x = radio.write(buf, sizeof(buf));
    _delay_ms(10);

    if(x) // send the key over radio
    {
        Serial.print("Send successful\n");
    }
    prevKey = buf[0];              // update the previous key
}