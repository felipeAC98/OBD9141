#include "Arduino.h"
// Be sure that the AltSoftSerial library is available, download it from http://www.pjrc.com/teensy/td_libs_AltSoftSerial.html"
#include "AltSoftSerial.h"


#include "OBD9141.h"

#define RX_PIN 8  // connect to transceiver Rx
#define TX_PIN 9  // connect to transceiver Tx
#define EN_PIN 10  //  pin will be set high (connect to EN pin of SN65HVDA100)
int RPM=0;
AltSoftSerial altSerial;

OBD9141 obd;


void setup(){
    Serial.begin(9600);
    delay(2000);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH); // enable the transceiver IC.

    obd.begin(altSerial, RX_PIN, TX_PIN);

}
    
void loop(){
    Serial.println("Loopingk");


    bool init_success =  obd.initKWP();
    Serial.print("init_success:");
    Serial.println(init_success);
    delay(50);

    //init_success = true;
    // Uncomment this line if you use the simulator to force the init to be
    // interpreted as successful. With an actual ECU; be sure that the init is 
    // succesful before trying to request PID's.

    if (init_success){
        bool res;
        while(1){
            /*res = obd.getCurrentPID(0x11, 1);
            if (res){
                Serial.print("Result 0x11 (throttle): ");
                Serial.println(obd.readUint8());
            }*/
            
            res = obd.getCurrentPID(0x0C, 2);
            if (res){
                Serial.print("Result 0x0C (RPM): ");
                RPM=obd.readUint16()/4;
                Serial.println(RPM);
            }


            /*res = obd.getCurrentPID(0x0D, 1);
            if (res){
                Serial.print("Result 0x0D (speed): ");
                Serial.println(obd.readUint8());
            }*/
            Serial.println();

            delay(200);
        }
    }
    delay(3000);//*/
}




