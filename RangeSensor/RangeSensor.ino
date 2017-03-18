/*
 * Created for the Facility Management Application
 * The application was developped for ELEC 390 - Team Design Project
*/

#include <SPI.h>
#include <Ethernet2.h>
#include <EEPROM.h>
#include "sensorData.h"
#include "Arduino.h"
#include "aJSON.h"

//---------------------------Variable Declaration-------------------------------------

//Assigning the sensor analog entry to pin A0.
int sensorPin = A0;

//Assigning the red LED to pin 8
int BLUELED = 11; //Blinks if the internet connection could not be established.
int REDLED = 10; //Blinks if the server connection could not be established.

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
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xC9, 0x4A};

//IP adress of the server.
IPAddress ip(192,168,1,110) ;

//Server IP adress.
IPAdress server(192.168.1.300); 

// Initializing the Ethernet client.
EthernetClient client;

//---------------------------------------------------------------------------------

void setup() {
  
  Serial.begin(9600);  // Open serial communication port. 
  pinMode(REDLED, OUTPUT);  //Configure REDLED pin as an input or output.
  pinMode(BLUELED, OUTPUT); //Configure BLUELED pin as an input or output.
  connectionFlag = false; //Set the connection flag to false.
  serverFlag = false;
  //Starting the Ethernet connection
  if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP"); //Print error message if the connection with the internet failed. 
      connectionFlag = false; //Set the connection flag to false.
  }

//----------------------------TESTING INTERNET---------------------------------------------
  /*// Print your local IP address, to confirm that the device is connecte to the network.
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) { // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
//----------------------------------------------------------------------------------------------*/
  //}
}
void loop() { // Void loop contains the code that will be runned reapeatidly.
  
  //Check for the state of the network connection of the microcontroller.
  if (connectionFlag == false)
    {
      digitalWrite(BLUELED, HIGH);  //Turn on the LED assigned to the integer pin.
    }

  //Check for the state of the server connection of the microcontroller.
  if (serverFlag == false)
    {
      digitalWrite(REDLED, HIGH); //The red LED on the device will blink if the connection to the server is not successful
    }
  if (client.available()){
    readRequest();
    sendRequest();  //Sends data to database, if check_data is true
  }
  
  datareading.setsensorData(sensorPin); 
  tempReading = datareading.getRange();
  //Serial.println(tempReading); //Serial monitoring of the range
      
	//Detection algorithm
	datareading.insert(tempReading);	//Insert Data
	datareading.algorithm_shift();	//Shift Data to the right
  if(datareading.check_data() == true) //Check the return state of the check_data function
    {
      Serial.println("ENTRY");	//Displays entry on the serial display if there is an enrty (Used for testing)
      sendToDatabase(datareading);
      datareading.increment();
    }
   
 delay(150);   //Wait 25 millisecond before next reading
}

void sendToDatabase (sensorData data){ //Void function that will send a HTTP request to push data on the server. 
 EthernetClient client = server.available();
  if (client == true) {
    server.write("MESSAGE RECEIVED");
    //server.write(datareading.getcount());
}
/*String buildDeviceStatusJson()
{ 
  String data = "{";
  data+="\n"; 
  data+="\"WaterDetected\": ";
  data+=(int)isWaterDetected;  
  data+="\n";
  data+="}"; 
  return data; 
}

String readRequest(){
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  return request;
  }
  
void sendRequest(){
   // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  String webpage = "<head><meta http-equiv=""refresh"" content=""1""></head>";
  webpage += "<body>";
  webpage += "Count: ";
  webpage += "1";
  webpage += "</body></html>";
  client.println(webpage);
  
  Serial.println("Client disconnected");
  Serial.println("");
 }
  
void ledBlink (int pin) //Void function that will allow a given LED to blink.
{
  digitalWrite(pin, HIGH);  //Turn on the LED assigned to the integer pin.
  delay(1000);  //Wait for 1000 miliseconds
  digitalWrite(pin, LOW); //Turn of the LED assigned to the integer pin.
  delay(1000);  //Wait for 1000 miliseconds
}
*/


