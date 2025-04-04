#define _CRT_SECURE_NO_WARNINGS
#include "commons.h"
#include "pathfinding.h"
#include "classes.h"
#include "func.h"
#include "graphManip.h"

int main()
{
	int citiesCount = 0, w = 0, h = 0;
	Cities* first = nullptr;
	scanf("%d %d", &w, &h);
	char** map = new char* [h];
	for (int i = 0; i < h; i++)
		map[i] = new char[w];

	findCities(w, h, map, first, citiesCount);

	Nodes** hashTable = new Nodes* [citiesCount];
	for (int i = 0; i < citiesCount; i++)
		hashTable[i] = nullptr;

	fillCityDetails(w, h, map, hashTable, first, citiesCount);
	parseFlights(hashTable, citiesCount);
	parseQueries(hashTable, first, citiesCount);
	deleteContents(hashTable, first, citiesCount);

	return 0;
}