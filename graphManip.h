#pragma once
#include "commons.h"
#include "classes.h"
#include "pathfinding.h"

void findCities(int w, int h, char** map, Cities*& first, int& citiesCount);
void fillCityDetails(int w, int h, char** map, Nodes** hashTable, Cities* first, int citiesCount);
void parseFlights(Nodes** hashTable, int citiesCount);
void parseQueries(Nodes** hashTable, Cities* cities, int citiesCount);
void deleteContents(Nodes** hashTable, Cities* cities, int citiesCount);