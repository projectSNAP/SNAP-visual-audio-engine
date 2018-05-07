#include "config_module.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using namespace std;
using namespace nlohmann;

namespace config {

/**
 * @brief      Loads a configuration from a .json file.
 *
 * @param      filePath the path to the .json file.
 */
config_type load(string filePath)
{
	json jsonConfig;
	config_type newConfig;
	try {
		cout << "Opening Config File: " << filePath << endl;
		ifstream inputFile(filePath);
		inputFile >> jsonConfig;
		set_int_config(jsonConfig, "horizontalResolution", newConfig.horizontalResolution);
		set_int_config(jsonConfig, "verticalResolution", newConfig.verticalResolution);
		set_int_config(jsonConfig, "cycleLength", newConfig.cycleLength);
		set_float_config(jsonConfig, "fieldOfView", newConfig.fieldOfView);
		set_float_config(jsonConfig, "sampleLength", newConfig.sampleLength);
		set_float_config(jsonConfig, "frequencyMin", newConfig.frequencyMin);
		set_float_config(jsonConfig, "frequencyMax", newConfig.frequencyMax);
		set_scanning_type_config(jsonConfig, "scanningType", newConfig.scanningType);
		set_sound_gradient_config(jsonConfig, "distanceIndicator", newConfig.distanceIndicator);
		set_sound_gradient_config(jsonConfig, "heightIndicator", newConfig.heightIndicator);
	}
	catch (json::parse_error &e) {
		cerr << e.what() << endl;
		cerr << "Error reading file, defaults will be used." << endl;
	}
	return newConfig;
}

bool is_number(json jsonConfig, const string name) {
	if (jsonConfig.find(name) != jsonConfig.end()) {
		if ( jsonConfig[name].type() == json::value_t::number_integer
		        || jsonConfig[name].type() == json::value_t::number_unsigned
		        || jsonConfig[name].type() == json::value_t::number_float) {
			return true;
		}
	}
	return false;
}

bool is_string(json config, const string name) {
	if (config.find(name) != config.end()) {
		if ( config[name].type() == json::value_t::string) {
			return true;
		}
	}
	return false;
}


void set_int_config(nlohmann::json config, const string name, int &destination) {
	if (is_number(config, name)) {
		destination = config[name];
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
	else {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
	}
}

void set_float_config(json config, const string name, float &destination) {
	if (is_number(config, name)) {
		destination = config[name];
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
	else {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
	}
}

void set_scanning_type_config(json config, const string name, ScanningType &destination) {
	bool error = false;
	if (is_number(config, name)) {
		switch ((int)config[name]) {
		case LATERAL_RIGHT:
			destination = LATERAL_RIGHT;
			break;
		case LATERAL_LEFT:
			destination = LATERAL_LEFT;
			break;
		case BILATERAL:
			destination = BILATERAL;
			break;
		case SPLIT_LATERAL_OUT:
			destination = SPLIT_LATERAL_OUT;
			break;
		case SPLIT_LATERAL_IN:
			destination = SPLIT_LATERAL_IN;
			break;
		case SPLIT_BILATERAL:
			destination = SPLIT_BILATERAL;
			break;
		default:
			error = true;
		}
	} else {
		error = true;
	}

	if (error) {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
	} else {
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
}

void set_sound_gradient_config(json config, string name, SoundGradient &destination) {
	bool error = false;
	if (is_number(config, name)) {
		switch ((int)config[name]) {
		case FREQUENCY:
			destination = FREQUENCY;
			break;
		case SINE_TO_SQUARE:
			destination = SINE_TO_SQUARE;
			break;
		case SQUARE_TO_SINE:
			destination = SQUARE_TO_SINE;
			break;
		case VOLUME:
			destination = VOLUME;
			break;
		default:
			error = true;
		}
	} else {
		error = true;
	}

	if (error) {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
	} else {
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
}

void print(config_type config) {
	printf("%d \n", config.horizontalResolution);
	printf("%d \n", config.verticalResolution);
	printf("%d \n", config.cycleLength);
	printf("%f \n", config.fieldOfView);
	printf("%f \n", config.sampleLength);
	printf("%f \n", config.frequencyMin);
	printf("%f \n", config.frequencyMax);
	printf("%d \n", config.scanningType);
	printf("%d \n", config.distanceIndicator);
	printf("%d \n", config.heightIndicator);
}

}