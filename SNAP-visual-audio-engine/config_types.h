#pragma once

#include <string>

namespace config {

const int scanningTypeStringsCount = 6;

typedef enum ScanningType {
	LATERAL_RIGHT,
	LATERAL_LEFT,
	BILATERAL,
	SPLIT_LATERAL_OUT,
	SPLIT_LATERAL_IN,
	SPLIT_BILATERAL,
} ScanningType;

const std::string scanningTypeStrings[scanningTypeStringsCount] = {
	"LATERAL_RIGHT",
	"LATERAL_LEFT",
	"BILATERAL",
	"SPLIT_LATERAL_OUT",
	"SPLIT_LATERAL_IN",
	"SPLIT_BILATERAL"
};

const int soundGradientCount = 4;

typedef enum SoundGradient {
	FREQUENCY,
	SINE_TO_SQUARE,
	SQUARE_TO_SINE,
	VOLUME
} SoundGradient;

const std::string soundGradientStrings[soundGradientCount] = {
	"FREQUENCY",
	"SINE_TO_SQUARE",
	"SQUARE_TO_SINE",
	"VOLUME"
};

typedef struct config_type {
	int horizontalResolution;
	int verticalResolution;
	int cycleLength;
	float fieldOfView;
	float sampleLength;
	float amplitude;
	float frequencyMin;
	float frequencyMax;
	ScanningType scanningType;
	SoundGradient distanceIndicator;
	SoundGradient heightIndicator;
	config_type() {
		horizontalResolution = 32;
		verticalResolution = 16;
		fieldOfView = 90.f;
		sampleLength = 1.f;
		frequencyMin = 110.f;
		frequencyMax = 440.f;
		cycleLength = 1000;
		scanningType = BILATERAL;
		distanceIndicator = VOLUME;
		heightIndicator = FREQUENCY;
	}
} config_type;
}