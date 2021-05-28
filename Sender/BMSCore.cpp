/**************************************************************************************
* @file        : BMSCore.cpp
* @brief       :
*
**************************************************************************************/

#ifndef BMSCORE_CPP_
#define BMSCORE_CPP_

#include <stdlib.h>
#include "BMSCore.h"

BMS::BMS()
{

}

BMS::~BMS()
{

}

float randDouble_ZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}

int randInt_ZeroToHundred()
{
	return rand() % 100;
}


float BMS::getSoCReading()
{
	return randDouble_ZeroToOne();
}

int BMS::getTemperatureReading()
{
	return randInt_ZeroToHundred();
}


void BMS::readBatteryParametersInput()
{
	parameterData.SoC         = getSoCReading();
	parameterData.temperature = getTemperatureReading();
}

BatteryParameterDataStruct BMS::outputBatteryParameterData()
{
	return parameterData;
}




#endif /* BMSCORE_CPP_ */
