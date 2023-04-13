#pragma once

#if defined(_WIN32) || defined(__CYGWIN__) || defined(_WIN64)
	#define CLEAR_COMMAND "cls" // Windows
#elif defined(__linux__)
	#define CLEAR_COMMAND "clear" // Linux
#endif
