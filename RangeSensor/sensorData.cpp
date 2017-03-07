/*
 * sensorData.cpp file
 * Created for the Facility Management Application
 * The application was developped for ELEC 390 - Team Design Projec
*/

#include "Arduino.h"
#include "sensorData.h"
#include "time.h"

using namespace std;

sensorData::sensorData(){
}

void sensorData::setsensorData(int anPin)
{
	double anVolt;  //Temporary variable declaration. 
  anVolt = analogRead(anPin); //Assigns the analog reading to a temporary double variable. 
  measuredRange = anVolt*5; //Takes analog bit count and converts it to mm. (5mm per bit).
}

void sensorData::setTime(int month, int day, int hour, int minute)
{
	
}

int sensorData::getRange() {
  return measuredRange;
}

int sensorData::getTimeYear() {
	return measuredRange[0];
}

int sensorData::getTimeMonth() {
	return entryTime[1];
}

int sensorData::getTimeDay() {
  return entryTime[2];
}

int sensorData::getTimeHour() {
  return entryTime[3];
}

int sensorData::getTimeMinute() {
  return entryTime[4];
}
