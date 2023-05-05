#pragma once

#pragma warning(suppress : 4996)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNIGNS

// Consts
#define SEMESTERS_NUMBER 9
#define SUBJECTS_NUMBER 10

// Commands
#if defined(_WIN32) || defined(__CYGWIN__) || defined(_WIN64)
	#define CLEAR_COMMAND "cls" // Windows
#elif defined(__linux__)
	#define CLEAR_COMMAND "clear" // Linux
#endif

#define ESCAPE_STRING "{{ESC}}"

// Buttons
#define ESC 0x1b

#define ARROW_UP 0x48
#define ARROW_LEFT 0x4b
#define ARROW_RIGHT 0x4d
#define ARROW_DOWN 0x50

#define BACKSPACE 0x8

#define ENTER 0xD

// Time
#define SLEEP 15

// Colors

#define RESET   "\033[0m"
#define BLACK   "\033[30m"					/* Black */
#define RED     "\033[31m"					/* Red */
#define GREEN   "\033[32m"					/* Green */
#define YELLOW  "\033[33m"					/* Yellow */
#define BLUE    "\033[34m"					/* Blue */
#define MAGENTA "\033[35m"					/* Magenta */
#define CYAN    "\033[36m"					/* Cyan */
#define WHITE   "\033[37m"					/* White */
#define BOLDBLACK   "\033[1m\033[30m"		/* Bold Black */
#define BOLDRED     "\033[1m\033[31m"		/* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"		/* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"		/* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"		/* Bold White */

