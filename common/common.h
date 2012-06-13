#pragma once

#ifdef __MINGW32__
#define MINGW
#endif
#ifdef _MSC_VER
#define MSVC
#endif
#ifdef _DEBUG
#define DEBUG
#endif


#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef M_PI//for some reason MSVC math.h didnt define this
#define M_PI       3.14159265358979323846
#endif
#define DEG2RAD ((M_PI/180.f))
#define EPSILON  FLT_EPSILON
#ifdef MSVC
#define __func__  __FUNCTION__
#define BREAK __asm int 3//cause a breakpoint/crash
#define fseek _fseeki64
#endif

#define Ob(x)  ((unsigned)Ob_(0 ## x ## uL))
#define Ob_(x) (x & 1 | x >> 2 & 2 | x >> 4 & 4 | x >> 6 & 8 |		\
	x >> 8 & 16 | x >> 10 & 32 | x >> 12 & 64 | x >> 14 & 128)
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef size_t spos;

#ifndef MSVC
#define BREAK asm("int $3")
#endif



/**
    \internal
    Just like printf()
    */
void _debug(const char *format, ...);

/**
    \internal
    Just like printf()
    */
#include <stdarg.h>
void _print(const char *format, ...);
#define WHERESTRD  "[%s(): %d] DEBUG "
#define WHERESTRP  "[%s(): %d] "
#define WHEREARGP  __func__, __LINE__
#define DEBUGPRINT2D(...)       _debug(__VA_ARGS__)
#define DEBUGPRINT2P(...)       _print(__VA_ARGS__)

/**
    Prints the included text, with line number

    Use print just like you would printf.  It will automatically add the position
        from where it was called.  Depending on the current debug setting, print()
        will print to the console, log file, or not at all.

    \note requires the use of atleast one variable
    \see prints debug error
    */
#define print(_fmt, ...)  DEBUGPRINT2P(WHERESTRP _fmt, WHEREARGP, __VA_ARGS__)

/**
    Prints the included text, with line number

    Use warn just like you would printf.  It will automatically add the position
        from where it was called.  Depending on the current debug setting, print()
        will print to the console, log file, or not at all.

    \note requires the use of atleast one variable
    \see prints debug error
    */
#define warn(_fmt, ...)  DEBUGPRINT2P(WHERESTRP _fmt, WHEREARGP, __VA_ARGS__)//?fix

/**
    Prints the included text, with line number

    Use debug just like you would printf.  It will automatically add the position
        from where it was called.  Depending on the current debug setting, print()
        will print to the console, log file, or not at all.

    \see print error debugs
    */
#define debug(_fmt, ...)  DEBUGPRINT2D(WHERESTRD _fmt, WHEREARGP, __VA_ARGS__)

/**
    Prints the included text, with line number

    Prints \a _fmt with the position from where it was called.
        Depending on the current debug setting, prints()
        will print to the console, log file, or not at all.

    \see print debugs errors
    */
#define prints(_fmt) DEBUGPRINT2P(WHERESTRP _fmt, WHEREARGP)

/**
    Checks if \a path exists

    \param path the path to the file in question
    \returns 1 if \a path exists, 0 otherwise
    */
int fileExists(const char *path);

/**
    Gets the path to a file given its name and extension

    This is for compatability purposes only, for platforms with restricted
        filesystems, and should always be used.

    \note Supports extensions with more than 3 letters,
		but you probably shouldnt be using those
    \param name The name of the file (with extension, but not folder name)
    \returns The complete path to the file, ready to be passed to a loading function
    \warning The file loading functions do not call this automatically
    */
string pathToFile(string name);

/**
    Extracts the extension from \a path

	\note Without .
    \param path The path to the file
    \returns The extension of \a path
    */
string getExt(string path);

/**
    Extracts the file name from \a path
    \note Includes extension
    \param path The path to the file
    \returns The file name pointed to by \a path
    */
string getFile(string path);

/**
    Extracts the file name from \a path
    \note Without extension
    \param path The path to the file
    \returns The file name pointed to by \a path
    */
string getFileName(string path);

/**
    Removes the file name and extension from a path

    \note Includes \ at the end
    \param path The path to parse
    \returns The path to the folder containing the file in \a path
    */
string getPath(string path);

size_t removeLeadingTrailingSpaces(string &str);

size_t find(string str,string characters,size_t start=0);
size_t find_not(string str,string characters,size_t start=0);

string i2s(int i);

bool isnumber(string str);

#define vectorFind(a,i,f) \
	for(i=0;i<a.size();i++) \
	{ \
		if(a[i]==f) \
			break; \
	}

extern string invisibleCharacers;
extern spos npos;

void _error(string file,const char *format, ...);
#define WHERESTR  "%d] ERROR in %s(): "
#define WHEREARG  __LINE__, __func__
#define DEBUGPRINT2(...)       _error((getFile(__FILE__)), __VA_ARGS__)

/**
    Prints the included text, with line number

    Use error just like you would printf.  It will automatically add the position
        from where it was called and the word ERROR in capital letters.
        Depending on the current debug setting, error()
        will print to the console, log file, or not at all.

    \see errors debug print
    */
#define error(_fmt, ...)  DEBUGPRINT2(WHERESTR _fmt, WHEREARG, __VA_ARGS__)

/**
    Prints the included text, with line number

    Prints \a _fmt with the position from where it was called
        and the word ERROR in capital letters.
        Depending on the current debug setting, errors()
        will print to the console, log file, or not at all.

    \see error debugs prints
    */
#define errors(_fmt)  DEBUGPRINT2(WHERESTR _fmt, WHEREARG)

/**
    Convenience function that prints a blank debug message

    \see debug
    */
#define debugHere() debug("\n",NULL)
#define NONE printf("");

void initCommon();