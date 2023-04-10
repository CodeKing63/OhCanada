/*
This firmware is exclusively for use with the Canbed standalon CAN bus module. 
At minimum it shoudl return serial information and poterntially utilize the universal CAN bus library.
THere are CANbed specific libraries being used here. However all additional arduino libraries should be viable.
*/

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

const int SPI_CS_PIN = 17;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin


void setup() {
    Serial.begin(115200);
    while(!Serial);
    while (CAN_OK != CAN.begin(CAN_500KBPS))    // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS FAIL!");
        delay(100);
    }
    Serial.println("CAN BUS OK!");
}

void canBed_V1(){
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Get data from ID: ");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
    }
};

void loop() {
    canBed_V1();
}