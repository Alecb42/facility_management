// reading a text file
#include <iostream>
#include <fstream>
#include <string>
//#include <sensorData.h>

using namespace std;


int main() {
	string line;
	ifstream myfile("testData.txt");
	if (myfile.is_open())
	{
		int temp;
		while (getline(myfile, line))
		{
			myfile >> temp;
			//datareading.insert(temp);
			//datareading.algorithm_shift();
			//datareading.algorithm_check();
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return 0;
}