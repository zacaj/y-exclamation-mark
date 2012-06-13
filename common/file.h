#pragma once
#include "common.h"
#include <stdio.h>
#include "vec3.h"

void wuchar(uchar n,FILE *fp);
void wuint(uint n,FILE *fp);
void wfloat(float n,FILE *fp);
void wstr(string str,FILE *fp);
void wvec3f(vec3f v,FILE *fp);
void wvec4f(vec4f v,FILE *fp);
void wvec4u(vec4u v,FILE *fp);
void wmat4f(mat4f m,FILE *fp);

uchar ruchar(FILE *fp);
uint ruint(FILE *fp);
float rfloat(FILE *fp);
string rstr(FILE *fp);
vec3f rvec3f(FILE *fp);
vec4f rvec4f(FILE *fp);
vec4u rvec4u(FILE *fp);
mat4f rmat4f(FILE *fp);

/**
    Skips to the end of the next occurance of \a str

    \note Skips to the END
    \param fp The file to search in
    \param str The string to search for in \a fp
    \see skipTo
    */
void skipToString(FILE *fp,char *str);

/**
    Skips to the letter after the next occurance \a g

    \note Skips to the letter AFTER \a g
    \param fp The file to search in
    \param g The character to search for
    \see skipToString readTo
    */
void skipTo(FILE *fp,char g);

/**
    Skips backwards to the letter after the next occurance of \a g

    \note Skips to the letter AFTER \a g
    \param fp The file to search in
    \param g The character to search for
    \see skipToString readTo
    */
void skipBackTo(FILE *fp,char g);

/**
    Skips backwards to the first letter that is not \a g

    \note Skips to the letter AFTER the first letter that isnt \a g
    \param fp The file to search in
    \param g The character to search for
    \returns The letter it stopped at
    */
char skipBackWhile(FILE *fp,char g);

/**
    Skips  to the first letter that is not \a g

    \note Skips to the letter AFTER the first letter that isnt \a g
    \param fp The file to search in
    \param g The character to search for
    \returns The letter it stopped at
    */
char skipWhile(FILE *fp,char g);

/**
    Reads the characters to the first ocurrance of \a g

    \param fp The file to read from
    \param g The character to stop at
    \returns The characters between the current position in \a fp and \a g, not including \a g as a String
    \see String skipTo
    */
string readTo(FILE *fp,char g);