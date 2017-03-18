#pragma once
/*
* sensorData.h file
* Created for the Facility Management Application
* The application was developped for ELEC 390 - Team Design Project
*/
#include <time.h>
class sensorData //sensorData class declaration. 
{
private:
	int entryTime[5]; //Contains in order: year, month, day, hour, minutes.
	int measuredRange; //Contains the value of the range read, in centimeters.
	long rangeBuffer[10]; //Contains the 10 last values that were read by the sensor.
  int counter;

public:
	sensorData(); //Constructor.

  void increment();
  
	//set functions of the sensorData class.
	void setTime(int, int, int, int, int);
	void setsensorData(int);
	void algorithm_shift();
	void Print();
	void insert(int);
	bool check_data();

	//get functions of the sensorData class.
	int getRange();  //Returns range as a double variable.
	int getTimeYear();  //Returns an integer containing the year that entry was read.
	int getTimeMonth(); //Returns an integer containing the month that entry was read.
	int getTimeDay(); //Returns an integer containing the day that entry was read.
	int getTimeHour();  //Returns an integer containing the hour that entry was read.
	int getTimeMinute();  //Returns an integer containing the minute that entry was read.
};



