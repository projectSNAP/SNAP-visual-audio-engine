#pragma once
#include "al.h"
#include "alc.h"

/**
 * @brief      A module contains all of the functions required to utilize openAL
 *             in an audio algorithm without needing to write all of the
 *             boilerplate code. It also handles programmatic generation of sine
 *             waves through the init_sine_buffers function. As well as an
 *             abstraction of source movement in source_set_pos. This
 *             abstraction accepts an x and y coordinate that correlates with
 *             the vertical and horizontal ‘resolution’ of the module and moves
 *             the sources incrementally in front of the listener within the
 *             field of view using spherical coordinates.
 */
class openal_module
{
public:
	openal_module(int width, int height, float FOV);
	~openal_module();
	void init_sine_buffers(int count, float length, float frequencyMin, float frequencyMax);
	void init_sources(int count);
	const unsigned int *get_sources();
	const unsigned int *get_buffers();
	void source_set_buffer(int buffer, int source);
	void source_play(int source);
	void source_stop(int source);
	void source_pause(int source);
	void source_set_pos(int x, int y);
	void source_set_pitch(int source, float addPitch);
	void source_set_gain(int source, float gain);
	float source_get_gain(int source);
	float source_get_theta(int source);
	void source_print_position(int source);
	static float deg_to_rad(float x);
	static float rad_to_deg(float x);
	static float zero_threshold(float num);
	static float normalize_angle(float angle);
	static float cartesian_to_spherical_rho(float x, float y, float z);
	static float cartesian_to_spherical_theta(float x, float y, float z);
	static float cartesian_to_spherical_phi(float x, float y, float z);
	static void cartesian_to_spherical(float x, float y, float z, float *rho, float *theta, float *phi);
	static void spherical_to_cartesian(float rho, float theta, float phi, float *x, float *y, float *z);
protected:
	float horizontalFOV;
	ALCdevice *device;
	ALCcontext *context;
	ALuint *sources;
	ALuint *buffers;
	//Bounds for grid
	int xMax;
	int yMax;
};

