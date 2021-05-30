/**************************************************************************************
* @file        : BMS_Sender.cpp
* @brief       :
*
**************************************************************************************/

#include <iostream>
#include <unistd.h>

#include "../BMS_Core/BMSCore.h"

using namespace std;

#define OUTPUT_INTERVAL_IN_SEC  1

void printToConsole(std::string data)
{
  cout<<data;
}

int main()
{
	BMS batteryObj;

	while(1)
	{
		string paramterData = batteryObj.getBatteryParametersData_JsonFormat_String();

		printToConsole(paramterData);

		sleep(OUTPUT_INTERVAL_IN_SEC);
	}

}



















