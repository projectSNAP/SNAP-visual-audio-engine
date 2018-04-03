#include "audio_config.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace nlohmann;

bool validate(json config, string name);

audio_config::audio_config()
{
	sourceResolution = 0;
	fieldOfView = 0;
	frequency = 0.0;
	horizontalSteps = 0;
	freqIncrement = 0.0;
	stepDelay = 0;
	audioSpreadDeg = 0;
	audioVolRollOff = 0;
}

/**
 * @brief      Loads the configurations from a .json file.
 * @details    [long description]
 *
 * @param      filePath  [description]
 */
void audio_config::load(string filePath)
{
	json config;
	ifstream inputFile(filePath);
	if (!inputFile) {
		cerr << "Input file could not be opened for reading. Config values set to default." << endl;
	}
	inputFile >> config;

	if (validate(config, "sourceResolution")) {
		sourceResolution = config["sourceResolution"];
	}
	if (validate(config, "fieldOfView")) {
		fieldOfView = config["fieldOfView"];
	}
	if (validate(config, "frequency")) {
		frequency = config["frequency"];
	}
	if (validate(config, "horizontalSteps")) {
		horizontalSteps = config["horizontalSteps"];
	}
	if (validate(config, "freqIncrement")) {
		freqIncrement = config["freqIncrement"];
	}
	if (validate(config, "stepDelay")) {
		stepDelay = config["stepDelay"];
	}
	if (validate(config, "audioSpreadDeg")) {
		audioSpreadDeg = config["audioSpreadDeg"];
	}
	if (validate(config, "audioVolRollOff")) {
		audioVolRollOff = config["audioVolRollOff"];
	}
}

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