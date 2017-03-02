//sensorData cpp file
#include "Arduino.h"
#include "sensorData.h"


using namespace std;

sensorData::sensorData(){

}

void sensorData::setsensorData(int pin)
{
	//float voltage, voltage_mm;
	//voltage_mm = 5/1024;
	//voltage = analogRead(sensorPin);
	//measuredRange = 5 * (voltage/voltage_mm);
  measuredRange  = analogRead(pin);
}

void sensorData::setTime()
{
	time_t rawtime;
	time (&rawtime);
	acquisitionTime = asctime(localtime (&rawtime));
}

float sensorData::getRange() {
	return measuredRange;
}

int sensorData::getTime() {
	return acquisitionTime;
}
