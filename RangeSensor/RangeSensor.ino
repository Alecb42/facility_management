
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include "sensorData.h"
#include "Arduino.h"

//Variable Declaration
int sensorPin = A0; //Assigning the sensor analog entry to pin A0
int redLED = 8; //Assigning the red LED to pin 8
double tempReading, tempReading2;  //Contain the temporary readings that will be taken every time void loop() runs
sensorData datareading; //SensorData object that will store the range reading as a private data member


//Ethernet Settings
//Mac Adress from ethernet shield
byte mac[] = {0x90, 0xa2, 0xda, 0x10, 0xc9, 0xa4};

//Shield static ip address 
//IPAdress ip(192,168,0,177) ;

//Server ip adress
//IPAdress server(74, 125, 232, 128); 

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

int interval = 5000;  //Interval between data dumps

void setup() {
  // put your setup code here, to run once:
// initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //Initializing serial connection
  pinMode(redLED, OUTPUT);  //Setting pinmode output
  
  //if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    //Ethernet.begin(mac, ip);
    //Serial.println("Connected to: \n");
    //Serial.print("IP Address        : ");
    //Serial.println(Ethernet.localIP());
    //Serial.print("Subnet Mask       : ");
    //Serial.println(Ethernet.subnetMask());
    //Serial.print("Default Gateway IP: ");
    //Serial.println(Ethernet.gatewayIP());
    //Serial.print("DNS Server IP     : ");
    //Serial.println(Ethernet.dnsServerIP());
 // }
}

// Void loop contains the code that will be runned reapeatidly.
void loop() { 
  
  datareading.setsensorData(sensorPin);
  tempReading = datareading.getRange();
  tempReading2 = datareading.getVoltage();
  Serial.println(tempReading); //Serial monitoring of the range
  Serial.println(tempReading);
 // if (client == true)   //Check for connection
 // {
   digitalWrite(redLED, HIGH); //Opening the red LED if the client is connected
 // }
  
  //INSERT DETECTION ALGORITHM HERE
  //if(tempReading < 800.00) //Temporary algorithm
  //{
    //SENDING DATA TO THE SERVER
    //if(client.connected()){ //DATA SENT TO SERVER
    // Make a HTTP request:
    //client.print( "GET /add_data.php?");
    //client.print("serial=");
    //client.print( "RangeSensor" );
    //client.print("&&");
    //client.print("entry=");
    //client.print( "1");
    //client.print("&&");
    //client.print("time=");
    //client.print(entry_time);
    //client.println( " HTTP/1.1");
    //client.println( "Host: 192.168.2.9" );
    //client.println(server);
    //client.println( "Connection: close" );
    //client.println();
    //client.println();
    //client.stop();
    //}
  //}
  delay (100);
}
