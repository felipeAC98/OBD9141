#include "Arduino.h"
#include "OBD9141.h"
#include <iostream>

#define RX_PIN 0
#define TX_PIN 1
#define EN_PIN 2


OBD9141 obd;
    
while(1){
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH);

    obd.begin(Serial1, RX_PIN, TX_PIN);

    //Serial.println("Looping");
    std::cout << "Loop";

    // only change from reader is the init method here.
    bool init_success =  obd.initKWP();
    std::cout <<"init_success:";
    std::cout <<init_success<< endl;
    delay(50);

    //init_success = true;
    // Uncomment this line if you use the simulator to force the init to be
    // interpreted as successful. With an actual ECU; be sure that the init is 
    // succesful before trying to request PID's.

    if (init_success){
        bool res;
        while(1){
            res = obd.getCurrentPID(0x0C, 2);
            if (res){
                std::cout <<"Result 0x0C (RPM): ";
                std::cout <<obd.readUint16()/4 << endl;
            }
            delay(200);
        }
        delay(200);
    }
    delay(3000);
}
