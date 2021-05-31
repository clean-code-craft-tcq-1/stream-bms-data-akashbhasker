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
 * Description     : Method to check if condition to STOP Sending Parameter data is satisfied
 *                   Condition to stop : console input as "STOP"
 *
 */
void checkFor_Stop()
{
    std::string input;
    while(true && startflag)
    {
        std::cin >> input;
        if(input.compare(STOP_CONDITION) == SUCCESS)
        {
        	startflag = false;
        	break;
        }
    }
}

/**
 * Description     : Method to check if condition to START Sending Parameter data is satisfied
 *                   Condition to start : console input as "START"
 *                   Condition to get list of Parameters : console input as "GETPARAMS"
 *
 */
void checkFor_Start()
{
    std::string input;
    while(true)
    {
        std::cin >> input;
        if(input.compare(START_CONDITION) == SUCCESS)
        {
        	startflag = true;
        	break;
        }
        else if(input.compare(GET_PARAMS) == SUCCESS)
        {
        	BMS batteryObj;
        	cout<<batteryObj.getparametersList();
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
	checkFor_Start();
	std::thread inp(start_Sender);
	std::thread outp(checkFor_Stop);

	outp.join();
	inp.join();

	return 0;

}



















