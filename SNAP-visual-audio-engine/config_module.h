#pragma once

#include "config_types.h"
#include "json.hpp"

namespace config {

config_type load(std::string filePath);
bool iequals(const std::string a, const std::string b);
int string_in_array(const std::string str, const std::string* arr, int arrSize);
bool is_scantype(std::string str);
bool is_soundgradient(std::string str);
bool is_number(nlohmann::json jsonConfig, std::string name);
bool is_string(nlohmann::json jsonConfig, std::string name);
void set_int_config(nlohmann::json jsonConfig, std::string name, int &destination);
void set_float_config(nlohmann::json jsonConfig, std::string name, float &destination);
void set_scantype_config(nlohmann::json jsonConfig, std::string name, ScanType &destination);
void set_soundgradient_config(nlohmann::json jsonConfig, std::string name, SoundGradient &destination);

void print(config_type config);
}