#pragma once
#include "commons.h"
#include "classes.h"

void bfs(Cities* city, char** map, int maxX, int maxY, int** weights);
void printPath(Cities* end);
void dijkstra(Cities* front, Cities* start, Cities* end, int numCities, Nodes** hashTable, int path);