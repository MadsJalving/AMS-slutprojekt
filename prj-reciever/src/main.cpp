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
#include <printf.h>
#include <string.h>

#include <util/delay.h>

#include "motorControl.hpp"

RF24 radio(7, 8);

void initReceiver();
void getData();
void showData();

char buffer[32] = "";
bool newData = false;
const byte thisSlaveAddress[6] = "00002";

int main()
{
    init();
    Serial.begin(9600);
    
    while(!Serial)
    {}
    printf_begin();

    Serial.print(F("Hello from Receiver\n"));

    initReceiver();
    radio.printPrettyDetails();

    for(;;)
    {
        getData();
        showData();
        // if (radio.available()) {

            // switch (buffer)
            // {
            //     case 'w':
            //         Serial.println("Key W is pressed");
            //         break;

            //     case 'a':
            //         Serial.println("Key A is pressed");
            //         break;

            //     case 's':
            //         Serial.println("Key S is pressed");
            //         break;

            //     case 'd':
            //         Serial.println("Key D is pressed");
            //         break;
              
            //     default:
            //         break;
            // }
        // }
    }
    return 0;
}

void initReceiver()
{
    // if(!radio.begin())
    // {
    //     Serial.print(F("    Radio hardware not responding!\n"));
    //     while(1){}
    // } 
    radio.begin();
    radio.openReadingPipe(0, thisSlaveAddress); //Setting the address at which we will receive the data 
    radio.setPALevel(RF24_PA_MIN);     //You can set this as minimum or maximum depending on the distance between the transmitter and receiver. 
    radio.setDataRate(RF24_250KBPS);
    radio.startListening();            //This sets the module as receiver
    radio.setChannel(76);
}

void getData()
{
    if (radio.available()) {
        radio.read(&buffer, sizeof(buffer));
        newData = true;
    }
}

void showData()
{
    if (newData) {
        Serial.print("Data received ");
        String dataString = String(buffer);
        Serial.println(dataString);
        newData = false;
    }
}