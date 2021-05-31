/**************************************************************************************
* @file        : BMS_Sender.cpp
* @brief       :
*
**************************************************************************************/

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

#include "../BMS_Core/BMSCore.h"

using namespace std;

#define START_CONDITION "START"
#define STOP_CONDITION  "STOP"
#define GET_PARAMS      "GETPARAMS"
#define OUTPUT_INTERVAL_IN_SEC  1
#define SUCCESS  0

bool startflag = false;

/**
 * Description     : Method to print provided string data to console
 *
 */
void printToConsole(std::string data)
{
  std::cout<<data;
}

/**
 * Description     : Method to check and handle console input
 *                   Condition to start : console input as "START"
 *                   Condition to stop : console input as "STOP"
 *                   Condition to get list of Parameters : console input as "GETPARAMS"
 *
 */
bool checkFor_Input()
{
	std::string input;
	{
		while(true)
		{
			std::cin >> input;

			if(input.compare(GET_PARAMS) == SUCCESS)
			{
				BMS batteryObj;
				cout<<batteryObj.getparametersList();
			}
			else if(startflag && input.compare(STOP_CONDITION) == SUCCESS)
			{
				startflag = false;
				return false;
			}
			if(!startflag &&  input.compare(START_CONDITION) == SUCCESS)
			{
				startflag = true;
				return true;
			}
		}
	}
}

/**
 * Description     : Method to read the current state of Battery Parameters and print to console
 *                   Output format : {"Parameter_1":"data","Parameter_2":"data"}
 *
 */
void start_Sender()
{
	BMS batteryObj;

	while(true && startflag)
	{
		string paramterData = batteryObj.getBatteryParametersData_JsonFormat_String();

		printToConsole(paramterData);

		std::this_thread::sleep_for (std::chrono::seconds(OUTPUT_INTERVAL_IN_SEC));
	}
}

/**
 * Description     : Main Method
 *
 */
int main()
{
	bool startSender = checkFor_Input();
	if(startSender)
	{
		std::thread inp(start_Sender);
		std::thread outp(checkFor_Input);

		outp.join();
		inp.join();
	}

	return 0;

}



















