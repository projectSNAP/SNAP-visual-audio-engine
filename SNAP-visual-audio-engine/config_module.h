#pragma once

#include "config_types.h"
#include "json.hpp"

/**
 * This module contains all of the functions necessary for reading
 * configurations for the Visual Audio Engine configurations from JSON formatted
 * files.
 */
namespace config {
// TODO: validate each input to make sure it's within a reasonable range
// such as 0 - 16 for verticalResolution.
config_type load(std::string filePath);
bool iequals(const std::string a, const std::string b);
int string_in_array(const std::string str, const std::string* arr, int arrSize);
bool is_scanningType(std::string str);
bool is_soundgradient(std::string str);
bool is_number(nlohmann::json jsonConfig, std::string name);
bool is_string(nlohmann::json jsonConfig, std::string name);
void set_int_config(nlohmann::json jsonConfig, std::string name, int &destination);
void set_float_config(nlohmann::json jsonConfig, std::string name, float &destination);
void set_scanning_type_config(nlohmann::json jsonConfig, std::string name, ScanningType &destination);
void set_sound_gradient_config(nlohmann::json jsonConfig, std::string name, SoundGradient &destination);

void print(config_type config);
}