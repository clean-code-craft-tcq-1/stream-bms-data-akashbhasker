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
#define SET_OUPUTRATE   "SETOUTPUTRATE"
#define SUCCESS  0

bool startflag = false;
int outputRate_in_ms = 1000;

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
 *                   Condition to start                  : console input as "START"
 *                   Condition to stop                   : console input as "STOP"
 *                   Condition to get list of Parameters : console input as "GETPARAMS"
 *                   Condition to set output Rate        : console input as "SETOUTPUTRATE rate_in_ms"
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
			else if(!startflag &&  input.compare(START_CONDITION) == SUCCESS)
			{
				startflag = true;
				return true;
			}
			else if(input.compare(SET_OUPUTRATE) == SUCCESS)
			{
				unsigned int outputrate = 1000;
				cin>>outputrate;
				if(outputrate != 0)
				{
					outputRate_in_ms = outputrate;
				}
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

		std::this_thread::sleep_for (std::chrono::milliseconds(outputRate_in_ms));
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



















