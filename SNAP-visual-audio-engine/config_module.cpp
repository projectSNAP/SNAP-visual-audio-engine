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
		set_int_config(jsonConfig, "savedHorizontalResolution", newConfig.horizontalResolution);
		set_int_config(jsonConfig, "savedVerticalResolution", newConfig.verticalResolution);
		set_int_config(jsonConfig, "savedCycleLength", newConfig.cycleLength);
		set_float_config(jsonConfig, "savedFieldOfView", newConfig.fieldOfView);
		set_float_config(jsonConfig, "savedSampleLength", newConfig.sampleLength);
		set_float_config(jsonConfig, "savedFrequencyMin", newConfig.frequencyMin);
		set_float_config(jsonConfig, "savedFrequencyMax", newConfig.frequencyMax);
		set_scantype_config(jsonConfig, "savedScanningType", newConfig.scanType);
		set_soundgradient_config(jsonConfig, "savedDistanceIndicator", newConfig.distanceIndicator);
		set_soundgradient_config(jsonConfig, "savedHeightIndicator", newConfig.heightIndicator);
	}
	catch (json::parse_error &e) {
		cerr << e.what() << endl;
		cerr << "Error reading file, defaults will be used." << endl;
	}
	return newConfig;
}

bool iequals(const string a, const string b)
{
	for (unsigned int i = 0; a[i] != '\0'; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

int string_in_array(const string str, const string* arr, int arrSize) {
	for (int i = 0; i < arrSize; i ++) {
		if (iequals(arr[i], str)) {
			return i;
		}
	}
	return -1;
}

bool is_scantype(const string str) {
	return string_in_array(str, scanTypeStrings, scanTypeStringsCount);
}

bool is_soundgradient(const string str) {
	return string_in_array(str, soundGradientStrings, soundGradientCount);
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

void set_scantype_config(json config, const string name, ScanType &destination) {
	if (is_number(config, name)) {
		destination = config[name];
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
	else {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
	}
}

void set_soundgradient_config(json config, string name, SoundGradient &destination) {
	if (is_number(config, name)) {
		destination = config[name];
		clog << "Config \"" << name << "\" was successfully set to " << destination << "." << endl;
	}
	else {
		cerr << "Config \"" << name << "\" could not be loaded. Default value " << destination << " will be used." << endl;
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
	printf("%d \n", config.scanType);
	printf("%d \n", config.distanceIndicator);
	printf("%d \n", config.heightIndicator);
}

}