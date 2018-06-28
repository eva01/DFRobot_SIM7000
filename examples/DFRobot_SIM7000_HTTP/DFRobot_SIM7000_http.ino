 /*
  * File  : DFRobot_SIM7000_HTTP.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example verify TCP connection over a HTTP request
  *         With initialization completed, we use connect(TCP,"www.taobao.com",80) to set TCP connection
  *         Then send a HTTP request to get the HEAD of taobao.com
  *         Thus we finished the TCP send and receive verification
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
#define serverIP   "www.sim.com"
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    while(!Serial);
    sim7000.begin(mySerial);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                                        //Turn ON SIM7000
        Serial.println("Turn ON !");
    }

    Serial.println("Set baud rate......");
    while(1){
        if(sim7000.setBaudRate(19200)){                                          //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
            Serial.println("Set baud rate:19200");
            break;
        }else{
            Serial.println("Faile to set baud rate");
            delay(1000);
        }
    }

    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                                                //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
        while(1);
    }

    Serial.println("Set net mode......");
    while(1){
        if(sim7000.setNetMode(NB)){                                              //Set net mod NB-IOT
            Serial.println("Set NB-IOT mode");
            break;
        }else{
            Serial.println("Fail to set mode");
            delay(1000);
        }
    }

    Serial.println("Get signal quality......");
    signalStrength=sim7000.checkSignalQuality();                                 //Check signal quality from (0-30)
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);

    Serial.println("Attaching service......");
    while(1){
        if(sim7000.attacthService()){                                            //Open the connection
            Serial.println("Attach service");
            break;
        }else{
            Serial.println("Fail to Attach service");
            delay(1000);
        }
    }

    Serial.println("Init http......");
    while(1){
        if(sim7000.HTTPinit(NB)){                                                //Init http server
            Serial.println("HTTP init !");
            break;
        }else{
            Serial.println("Fail to init http");
        }
    }

    Serial.print("Connect to ");
    Serial.print(serverIP);
    Serial.println("......");
    while(1){
        if(sim7000.HTTPconnect(serverIP)){                                       //Connect to server
            Serial.println("Connected !");
            break;
        }else{
            Serial.println("Fail to connect");
        }
    }

    Serial.println("POST ......");
    while(1){
        if(sim7000.HTTPpost("Enter POST data herr")){                            //HTTP POST
            Serial.println("Post successed");
            break;
        }else{
            Serial.println("Fail to post");
        }
    }

    Serial.println("GET ......");
    sim7000.HTTPget();                                                //HTTP GET

    Serial.println("Disconnect");
    sim7000.HTTPdisconnect();                                                    //Disconnect
    Serial.println("Close net work");
    sim7000.closeNetwork();                                                      //Close net work
    Serial.println("Turn off SIM7000");
    sim7000.turnOFF();                                                           //Turn OFF SIM7000
}

void loop() {
    delay(1000);
}