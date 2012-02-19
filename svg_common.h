// svg_common.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifdef _WIN32

#pragma once


#include <iostream>
#include <tchar.h>

#include <windows.h>
// TODO: reference additional headers your program requires here


#else



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int DWORD;

#ifndef NULL
#define NULL 0
#endif

#define _MAX_PATH	1024


#endif

