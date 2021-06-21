/**************************************************************************************
* @file        : BMS_Sender_Test.cpp
* @brief       :
*
**************************************************************************************/
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string.h>
#include <sstream>
#include <iostream>
#include <cctype>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "catch.hpp"
#include "../BMS_Core/BMSCore.h"

using boost::property_tree::ptree;

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool isFloat( std::string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

boost::property_tree::ptree getJsonFromString(std::string data)
{
	std::stringstream input;
	input.str(data);
	boost::property_tree::ptree Jsondata;
	boost::property_tree::json_parser::read_json(input,Jsondata);

	return Jsondata;
}


TEST_CASE("data generation test - NOT NULL") {

	BMS bmsTestObj;
	std::string paramterData = bmsTestObj.getBatteryParametersData_JsonFormat_String();

	REQUIRE(paramterData.empty() == false);

}

TEST_CASE("data generation test - Temperature with Integer data") {

	BMS bmsTestObj;

	boost::property_tree::ptree Jsondata = getJsonFromString(bmsTestObj.getBatteryParametersData_JsonFormat_String());
	ptree::const_iterator iter = Jsondata.begin();

	std::string parameterName = iter->first;
	std::string data  = iter->second.get_value<std::string>();


	REQUIRE( (parameterName == "Temperature_in_Celcius"));
	REQUIRE(isNumber(data) == true);

}

TEST_CASE("data generation test - SoC with Float Data") {

	BMS bmsTestObj;

	boost::property_tree::ptree Jsondata = getJsonFromString(bmsTestObj.getBatteryParametersData_JsonFormat_String());
	ptree::const_iterator iter = Jsondata.begin();
	++iter;

	std::string parameterName = iter->first;
	std::string data  = iter->second.get_value<std::string>();


	REQUIRE( (parameterName == "SoC_in_Percent"));
	REQUIRE(isFloat(data) == true);

}




