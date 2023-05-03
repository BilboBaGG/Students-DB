#pragma once

#if defined(_WIN32) || defined(__CYGWIN__) || defined(_WIN64)
	#define CLEAR_COMMAND "cls" // Windows
#elif defined(__linux__)
	#define CLEAR_COMMAND "clear" // Linux
#endif

#define ESC 0x1b

#define ARROW_UP 0x48
#define ARROW_LEFT 0x4b
#define ARROW_RIGHT 0x4d
#define ARROW_DOWN 0x50

#define BACKSPACE 0x8

#define ENTER 0xD

