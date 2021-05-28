/**************************************************************************************
* @file        : BMSCore.h
* @brief       :
*
**************************************************************************************/

#ifndef BMSCORE_H_
#define BMSCORE_H_

struct BatteryParameterDataStruct
{
	double SoC;
	int temperature;
};


class BMS
{
	BatteryParameterDataStruct parameterData;

	float getSoCReading();
	int getTemperatureReading();

public:
	BMS();
	~BMS();

	void readBatteryParametersInput();
	BatteryParameterDataStruct outputBatteryParameterData();

};


#endif /* BMSCORE_H_ */
