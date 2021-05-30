/**************************************************************************************
* @file        : BMSCore.cpp
* @brief       :
*
**************************************************************************************/

#ifndef BMSCORE_CPP_
#define BMSCORE_CPP_

#include <stdlib.h>
#include <sstream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


#include "BMSCore.h"

using namespace std;

float randFloat_ZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}

int randInt_ZeroToHundred()
{
	return rand() % 100;
}


float BMS::getSoCReading()
{
	return randFloat_ZeroToOne();
}

int BMS::getTemperatureReading()
{
	return randInt_ZeroToHundred();
}


BatteryParameterDataStruct BMS::readBatteryParametersInput_FromSensors()
{
	BatteryParameterDataStruct parameterData;
	parameterData.SoC         = getSoCReading();
	parameterData.temperature = getTemperatureReading();

	return parameterData;
}

string BMS::getBatteryParametersData_JsonFormat_String()
{
	BatteryParameterDataStruct parameterData  = readBatteryParametersInput_FromSensors();
	return formatOutputToJson(parameterData);
}

string BMS::formatOutputToJson(BatteryParameterDataStruct parameterdata)
{
	boost::property_tree::ptree Jsondata;

	float SOC= parameterdata.SoC;
	int Temperature = parameterdata.temperature;

	Jsondata.put("Temperature_in_Celcius", Temperature);
	Jsondata.put("SoC_in_Percent", SOC);

	stringstream output;
	boost::property_tree::json_parser::write_json(output, Jsondata,false);

	return output.str();
}




#endif /* BMSCORE_CPP_ */
