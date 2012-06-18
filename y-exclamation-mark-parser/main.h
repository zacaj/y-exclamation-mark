#pragma once
#include "common.h"

extern int realLineNumber;
void checkErrors(bool isError,string description);

#define WHERESTRE  "ERROR %i: "
#define WHEREARGE  realLineNumber
#define DEBUGPRINT2E(...)       _print(__VA_ARGS__)

/**
    Prints the included text, with line number

    Use error just like you would printf.  It will automatically add the position
        from where it was called and the word ERROR in capital letters.
        Depending on the current debug setting, error()
        will print to the console, log file, or not at all.

    \see errors debug print
    */
#define checkError(is,_fmt, ...)  \
	{{ \
		if(is) \
		{ \
			DEBUGPRINT2E(WHERESTRE _fmt, WHEREARGE, __VA_ARGS__); \
			BREAK \
		} \
	} \
}