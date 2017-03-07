/*
 * Created for the Facility Management Application
 * The application was developped for ELEC 390 - Team Design Project
*/

#include <SPI.h>
#include <Ethernet2.h>
#include <EEPROM.h>
#include "sensorData.h"
#include "Arduino.h"

//---------------------------Variable Declaration-------------------------------------

//Assigning the sensor analog entry to pin A0.
int sensorPin = A0;

//Assigning the red LED to pin 8
int BLUELED = 11; //Blinks if the internet connection could not be established.
int REDLED = 12; //Blinks if the server connection could not be established.

//Flag declaration
bool connectionFlag = true; //Will be set to false if the server cannot connect to the network.
bool serverFlag = true; //Will be set to false if the server cannot connect to the database. 

//Declaring variables to hold the temporary readings that will be taken every time void loop() runs.
double tempReading; 

//SensorData object that will store the range reading as a private data member.
sensorData datareading; 

//---------------------------------------------------------------------------------


//--------------------------Ethernet Settings--------------------------------------

//Mac Adress from ethernet shield.
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xC9, 0x4A};\

//IP adress of the server.
IPAddress ip(192,168,2,68) ;

//Server IP adress.
//IPAdress server(74, 125, 232, 128); 

// Initializing the Ethernet client.
EthernetClient client;

//---------------------------------------------------------------------------------

void setup() {
  
  Serial.begin(9600);  // Open serial communication port. 
  pinMode(REDLED, OUTPUT);  //Configure REDLED pin as an input or output.
  
  //Starting the Ethernet connection
  if (Ethernet.begin(mac) == 0) {
     Serial.println("Failed to configure Ethernet using DHCP"); //Print error message if the connection with the internet failed. 
     connectionFlag = false; //Set the connection flag to false.
  }
  
  // Print your local IP address, to confirm that the device is connecte to the network.
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) { // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}

void loop() { // Void loop contains the code that will be runned reapeatidly.
  
  //Check for the state of the network connection of the microcontroller.
  if (connectionFlag == false)
    {
      ledBlink(BLUELED); //The blue LED on the device will blink if the connection to internet was not successful
    }

  //Check for the state of the server connection of the microcontroller.
  if (serverFlag == false)
    {
      ledBlink(REDLED); //The red LED on the device will blink if the connection to the server is not successful
    }
    
  //If internet and server is connected, carry on with the data reading.
  else
    {
      datareading.setsensorData(sensorPin); 
      tempReading = datareading.getRange();
      Serial.println(tempReading); //Serial monitoring of the range
      
      //INSERT DETECTION ALGORITHM HERE
      if(tempReading < 600) //Temporary algorithm
        {
          Serial.println("ENTRY");
          //sendToDatabase();
        }
    }
 delay(25);   //Wait 25 millisecond before next reading
}

void sendToDatabase (sensorData dataObject){  //Void function that will send a HTTP request to push data on the server. 
  
  client.connect; ("http://www.test.com", 80) ;  //Connect the client Object to the address of the mySQL database.
  if (client.connected) //client.connected returns boolean true of false, will send data if true(connected).
    { 
      serverFlag = true;  //Set state of server to connected. 
      
      //The HTTP GET Request follows 
      client.print( "GET /testserver/facility/add_data.php?"); //Enter name of real server
      client.print("entry=");
      client.print( "1" );
      client.print("&&");
      client.print("month=");
      client.print(dataObject.getTimeMonth());
      client.print("&&");
      client.print("day=");
      client.print( dataObject.getTimeDay());
      client.print("&&");
      client.print("hours=");
      client.print( dataObject.getTimeHour());
      client.print("&&");
      client.print("minutes=");
      client.print( dataObject.getTimeMinute());
      client.println( " HTTP/1.1");
      client.print( "Host: test.com" );
      //client.println(server)
      client.println( "Connection: close" );
      client.println();
      client.println();
      client.stop();
    }
  else 
    {
      serverFlag = false; 
    }
}

void ledBlink (int pin) //Void function that will allow a given LED to blink.
{
  digitalWrite(pin, HIGH);  //Turn on the LED assigned to the integer pin.
  delay(1000);  //Wait for 1000 miliseconds
  digitalWrite(pin, LOW); //Turn of the LED assigned to the integer pin.
  delay(1000);  //Wait for 1000 miliseconds
}


