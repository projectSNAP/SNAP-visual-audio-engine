#include "config_module.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace nlohmann;

/**
 * @brief      Helper function to validate that the config is a number.
 * @details    Checks that the key exists in the config then verifies it's type.
 *
 * @param      config  Json object
 * @param      name    The key
 * @param      type    The type
 *
 * @return     True if valid, false if not.
 */
bool validate(json config, string name) {
	if (config.find(name) != config.end()) {
		if ( config[name].type() == json::value_t::number_integer
		        || config[name].type() == json::value_t::number_unsigned
		        || config[name].type() == json::value_t::number_float) {
			return true;
		}
	}
	cerr << "Config \"" << name << "\" could not be loaded." << endl;
	return false;
}

config_module::config_module()
{
	sourceResolutionVal = 16;
	fieldOfViewVal = 90;
	frequencyVal = 220.0;
	horizontalStepsVal = 10;
	freqIncrementVal = 0.0;
	stepDelayVal = 50;
	audioSpreadDegVal = 180;
	audioVolRollOffVal = 0;
}

/**
 * @brief      Loads the configurations from a .json file.
 * @details    [long description]
 *
 * @param      filePath  [description]
 */
void config_module::load(string filePath)
{
	json config;
	ifstream inputFile(filePath);
	if (!inputFile) {
		cerr << "Input file could not be opened for reading. Config values set to default." << endl;
	}
	inputFile >> config;

	if (validate(config, "sourceResolution")) {
		sourceResolutionVal = config["sourceResolution"];
	}
	if (validate(config, "fieldOfView")) {
		fieldOfViewVal = config["fieldOfView"];
	}
	if (validate(config, "frequency")) {
		frequencyVal = config["frequency"];
	}
	if (validate(config, "horizontalSteps")) {
		horizontalStepsVal = config["horizontalSteps"];
	}
	if (validate(config, "freqIncrement")) {
		freqIncrementVal = config["freqIncrement"];
	}
	if (validate(config, "stepDelay")) {
		stepDelayVal = config["stepDelay"];
	}
	if (validate(config, "audioSpreadDeg")) {
		audioSpreadDegVal = config["audioSpreadDeg"];
	}
	if (validate(config, "audioVolRollOff")) {
		audioVolRollOffVal = config["audioVolRollOff"];
	}
}


int config_module::sourceResolution(){
	return sourceResolutionVal;
}
int config_module::fieldOfView(){
	return fieldOfViewVal;
}
float config_module::frequency(){
	return frequencyVal;
}
int config_module::horizontalSteps(){
	return horizontalStepsVal;
}
float config_module::freqIncrement(){
	return freqIncrementVal;
}
int config_module::stepDelay(){
	return stepDelayVal;
}
float config_module::audioSpreadDeg(){
	return audioSpreadDegVal;
}
float config_module::audioVolRollOff(){
	return audioVolRollOffVal;
}