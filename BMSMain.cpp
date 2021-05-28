/**************************************************************************************
* @file        : BMSMain.cpp
* @brief       :
*
**************************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <sstream>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "BMSCore.h"

using namespace std;


#define OUTPUT_INTERVAL_IN_SEC  1

void printToConsole(std::string data)
{
  cout<<data;
}

stringstream formatOutputToJson(BatteryParameterDataStruct parameterdata)
{
	boost::property_tree::ptree Jsondata;

	float SOC= parameterdata.SoC;
	int Temperature = parameterdata.temperature;

	Jsondata.put("Temperature", Temperature);
	Jsondata.put("SOC", SOC);

	stringstream output;
	boost::property_tree::json_parser::write_json(output, Jsondata,false);

	return output;
}

void sendOutput(BatteryParameterDataStruct parameterdata)
{
   stringstream output = formatOutputToJson(parameterdata);
   printToConsole(output.str());
}

int main()
{
	BMS battery;
	while(1)
	{
		battery.readBatteryParametersInput();
		BatteryParameterDataStruct paramterData = battery.outputBatteryParameterData();
		sendOutput(paramterData);
		sleep(OUTPUT_INTERVAL_IN_SEC);
	}

}



















