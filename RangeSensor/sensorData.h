#ifndef sensorData_h
#define sensorData_h

#include <time.h>

class sensorData //friend to patient class
{ 
public:
  sensorData(); //Constructor
 // ~sensorData();  //Destructor

  //set functions
  void setTime();
  void setsensorData(int);

  //get functions
  double getRange();
  double getVoltage();
  int getTime();

private:
  int acquisitionTime;
  double measuredRange;
  double voltage;
};

#endif

