#ifndef __EFONT_M5STACK_H__
#define __EFONT_M5STACK_H__

#include <M5Unified.h>

void printEfont(char *str);
void printEfont(const String &str);

void printEfont(char *str, int x, int y);
void printEfont(const String &str, int x, int y);

void printEfont(char *str, int x, int y, int textsize);
void printEfont(const String &str, int x, int y, int textsize);

void printEfont(char *str, int x, int y, int textsizeX, int textsizeY);
void printEfont(const String &str, int x, int y, int textsizeX, int textsizeY);

void printEfont(M5Canvas *canvas, char *str);
void printEfont(M5Canvas *canvas, const char *str);
void printEfont(M5Canvas *canvas, const String &str);

void printEfont(M5Canvas *canvas, char *str, int x, int y);
void printEfont(M5Canvas *canvas, const char *str, int x, int y);
void printEfont(M5Canvas *canvas, const String &str, int x, int y);

void printEfont(M5Canvas *canvas, char *str, int x, int y, int textsize);
void printEfont(M5Canvas *canvas, const char *str, int x, int y, int textsize);
void printEfont(M5Canvas *canvas, const String &str, int x, int y, int textsize);

void printEfont(M5Canvas *canvas, char *str, int x, int y, int textsizeX, int textsizeY);
void printEfont(M5Canvas *canvas, const char *str, int x, int y, int textsizeX, int textsizeY);
void printEfont(M5Canvas *canvas, const String &str, int x, int y, int textsizeX, int textsizeY);

#endif //__EFONT_M5STACK_H__
