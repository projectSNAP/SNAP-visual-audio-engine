// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// TODO: reference additional headers your program requires here
#include <iostream>

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#include <conio.h>
	#include <stdio.h>
	#include <tchar.h>
	#include <direct.h>
#else
	//TODO: define linux equivalents of above
#endif