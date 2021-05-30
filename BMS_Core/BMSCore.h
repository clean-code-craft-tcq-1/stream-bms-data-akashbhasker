/**************************************************************************************
* @file        : BMSCore.h
* @brief       :
*
**************************************************************************************/

#include <string>

#ifndef BMSCORE_H_
#define BMSCORE_H_

struct BatteryParameterDataStruct
{
	double SoC;
	int temperature;
};


class BMS
{
	float getSoCReading();
	int getTemperatureReading();

public:
	BMS(){}
	~BMS(){}

	BatteryParameterDataStruct readBatteryParametersInput_FromSensors();
	std::string getBatteryParametersData_JsonFormat_String();

	static std::string formatOutputToJson(BatteryParameterDataStruct parameterdata);

};


#endif /* BMSCORE_H_ */
