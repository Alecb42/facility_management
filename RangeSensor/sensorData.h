/* 
 * sensorData.h file
 * Created for the Facility Management Application
 * The application was developped for ELEC 390 - Team Design Project
*/

#ifndef sensorData_h
#define sensorData_h

#include <time.h>

class sensorData //sensorData class declaration. 
{ 
public:
  sensorData(); //Constructor.
 // ~sensorData();  //Destructor.

  //set functions of the sensorData class.
  void setTime(int, int, int, int);
  void setsensorData(int);

  //get functions of the sensorData class.
  double getRange();  //Returns range as a double variable.
  int getTimeYear();  //Returns an integer containing the year that entry was read.
  int getTimeMonth(); //Returns an integer containing the month that entry was read.
  int getTimeDay(); //Returns an integer containing the day that entry was read.
  int getTimeHour();  //Returns an integer containing the hour that entry was read.
  int getTimeMinute();  //Returns an integer containing the minute that entry was read.
   
private:
  int[5] entryTime; //Contains in order: year, month, day, hour, minutes.
  double measuredRange; //Contains the value of the range read, in centimeters.
  double[10] rangeBuffer; //Contains the 10 last values that were read by the sensor.
};

#endif

