#include "sensorData.h"
#include "Arduino.h"
using namespace std;
sensorData::sensorData()
{
	entryTime[5] = {};
	measuredRange = 0;
	rangeBuffer[10] = {};
  counter=0;
}

void sensorData::increment()
{
  counter++;
}

void sensorData::setTime(int y, int m, int d, int h, int min){
	entryTime[0] = y;
	entryTime[1] = m;
	entryTime[2] = d;
	entryTime[3] = h;
	entryTime[4] = min;
}

void sensorData::setsensorData(int anPin){
	measuredRange = analogRead(anPin);
	measuredRange = measuredRange * 5; 
}

//This function allow data to be insert to array
void sensorData::insert(int data){
	rangeBuffer[0] = data;
}

//Shift the data to the right
void sensorData::algorithm_shift(){
	//shift your algorithm
	for (int i = 9; i > 0; i--){
		rangeBuffer[i] = rangeBuffer[i-1];
	}
}

bool sensorData::check_data(){
	//Assume the aproximated distance when someone enter the room
	int check_value = 630;
	int counter = 0;
	//Our Array will contains 10 data. In the testing, we noticed that the height was measured at
	//around 900 mm as it first opened when no one entered and began to fall down when someone entered 
	//the room. After that, the measured data increased again as that person started to move out of the sensor range. 
	//Hence, the desired data will be expected to gathered around the middle of the array.
	//The code below show my taken data. If there is at least 4 out of 10 less than the check value,
	//The sensor will count for 1 entry. Unless, no entry.
	for (int i = 0; i < 10; i++){
		if (rangeBuffer[i] < check_value) {
		//cout << "Entry Height " << i + 1 << ": " << rangeBuffer[i] << endl;
			counter++;
		}
	}
	if (counter >= 6){
//		cout << "MEET THE CONDITION -> ONE ENTRY" << endl;
   for (int i = 0; i < 10; i++){
    rangeBuffer[i] = 980; //RESETS THE VALUE IT ISNT COUNTED AGAIN
  }
		return true; //Condition satisfy -> count for 1 entry
	}
	else
		return false; //No entry
}

void sensorData::Print(){
	for (int i = 0; i < 10; i++){
		//cout << rangeBuffer[i] << " ";
	}
}

int sensorData::getRange() { return measuredRange;}  
int sensorData::getTimeYear() { return entryTime[0]; }  //Returns an integer containing the year that entry was read.
int sensorData::getTimeMonth() { return entryTime[1]; } //Returns an integer containing the month that entry was read.
int sensorData::getTimeDay() { return entryTime[2]; } //Returns an integer containing the day that entry was read.
int sensorData::getTimeHour() { return entryTime[3]; }  //Returns an integer containing the hour that entry was read.
int sensorData::getTimeMinute() { return entryTime[4];}  //Returns an integer containing the minute that entry was read.


