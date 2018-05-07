#pragma once

#include <string>

namespace config {

/**
 * Scanning type refferrs to the way (direction) that we scan the depth image
 * horizontally.
 */
typedef enum ScanningType {
	LATERAL_RIGHT = 0, // >>>>
	LATERAL_LEFT = 1, // <<<<
	BILATERAL = 2, // >>>> , <<<<
	SPLIT_LATERAL_OUT = 3, // <<>>
	SPLIT_LATERAL_IN = 4, // >><<
	SPLIT_BILATERAL = 5 // <<>> , >><<
} ScanningType;

/**
 * Sound Gradient refferrs to the gradient that represents the vertical axis of
 * the sound algorithm.
 */
typedef enum SoundGradient {
	FREQUENCY = 0,
	SINE_TO_SQUARE = 1,
	SQUARE_TO_SINE = 2,
	VOLUME = 3
} SoundGradient;

/**
 * Holds all of the current configurable components of a sound algorithm.
 */
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
		// Default configs for a sound algorithm.
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