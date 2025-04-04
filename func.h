#pragma once
#include "classes.h"

int generateHash(LiteString* str);
LiteString* checkForName(int x, int y, int maxX, char** map);
LiteString* findName(int x, int y, int maxX, int maxY, char** map);