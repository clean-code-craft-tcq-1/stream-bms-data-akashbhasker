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

/**
 * Description     : Method to get the current SoC reading
 *
 */
float BMS::getSoCReading()
{
	return randFloat_ZeroToOne();
}

/**
 * Description     : Method to get the current Temperature reading
 *
 */
int BMS::getTemperatureReading()
{
	return randInt_ZeroToHundred();
}

/**
 * Description     : Method to read and return the battery parameter state from Sensors
 *
 */
BatteryParameterDataStruct BMS::readBatteryParametersInput_FromSensors()
{
	BatteryParameterDataStruct parameterData;
	parameterData.SoC         = getSoCReading();
	parameterData.temperature = getTemperatureReading();

	return parameterData;
}

/**
 * Description     : Method to read the current batter parameter state and return it in JSON formatted string
 *
 */
string BMS::getBatteryParametersData_JsonFormat_String()
{
	BatteryParameterDataStruct parameterData  = readBatteryParametersInput_FromSensors();
	return formatOutputToJson(parameterData);
}

/**
 * Description     : Method to return the parameters list in JSON formatted string
 *                   Return String format : {"ParameterName_1":"dataType","ParameterName_2":"dataType"}
 *
 */
string BMS::getparametersList()
{
	BatteryParameterDataStruct data;
	boost::property_tree::ptree Jsondata;
	Jsondata.put("Temperature_in_Celcius", typeid(data.temperature).name());
	Jsondata.put("SoC_in_Percent", typeid(data.SoC).name());

	stringstream output;
	boost::property_tree::json_parser::write_json(output, Jsondata,false);

	return output.str();

}


/**
 * Description     : Utility Method to convert battery parameter data to string format
 *                   Return String format : {"Parameter_1":"data","Parameter_2":"data"}
 *
 */
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
