#pragma once

#include <string>

namespace config {

const int scanTypeStringsCount = 6;

typedef enum ScanType {
	LATERAL_RIGHT,
	LATERAL_LEFT,
	BILATERAL,
	SPLIT_LATERAL_OUT,
	SPLIT_LATERAL_IN,
	SPLIT_BILATERAL,
} ScanType;

const std::string scanTypeStrings[scanTypeStringsCount] = {
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
	ScanType scanType;
	SoundGradient distanceIndicator;
	SoundGradient heightIndicator;
	config_type() {
		horizontalResolution = 32;
		verticalResolution = 16;
		fieldOfView = 90.f;
		sampleLength = 1.f;
		amplitude = 1.f;
		frequencyMin = 110.f;
		frequencyMax = 440.f;
		cycleLength = 320;
		scanType = BILATERAL;
		distanceIndicator = VOLUME;
		heightIndicator = FREQUENCY;
	}
} config_type;
}