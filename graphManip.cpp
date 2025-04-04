#include "graphManip.h"

void findCities(int w, int h, char** map, Cities*& first, int& citiesCount)
{
	Cities* last = nullptr;
	for (int i = 0; i < h; i++)
	{
		getchar();
		for (int j = 0; j < w; j++)
		{
			map[i][j] = (char)getchar();
			if (map[i][j] == '*')
			{
				citiesCount++;
				if (first == nullptr)
				{
					first = new Cities(j, i);
					last = first;
				}
				else
				{
					last->next = new Cities(j, i);
					last = last->next;
				}
			}
		}
	}
}

void fillCityDetails(int w, int h, char** map, Nodes** hashTable, Cities* first, int citiesCount)
{
	int** weights = new int* [h];
	for (int j = 0; j < h; j++)
		weights[j] = new int[w];

	for (Cities* city = first; city != nullptr; city = city->next)
	{
		int dX, dY;
		bool state = false;
		city->x == 0 ? dX = 0 : dX = city->x - 1;
		for (dX; (dX <= city->x + 1) && (dX < w); dX++)
		{
			if (state == false)
			{
				city->y == 0 ? dY = 0 : dY = city->y - 1;
				for (dY; (dY <= city->y + 1) && (dY < h); dY++)
				{
					if (dX != city->x || dY != city->y)
					{
						LiteString* name = checkForName(dX, dY, w, map);
						if (name != nullptr)
						{
							city->name = name;
							state = true;
							break;
						}
					}
				}
			}
			else break;
		}

		int coordX[4] = { 1, -1, 0, 0 };
		int coordY[4] = { 0, 0, 1, -1 };
		for (int i = 0; i < 4; i++) {
			int nx = city->x + coordX[i], ny = city->y + coordY[i];
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && (map[ny][nx] == '#' || map[ny][nx] == '*'))
			{
				bfs(city, map, w, h, weights);
				break;
			}
		}
		city->hashify(hashTable, citiesCount);
	}

	for (int i = 0; i < h; i++)
	{
		delete[] map[i];
		delete[] weights[i];
	}
	delete[] map;
	delete[] weights;
}

void parseFlights(Nodes** hashTable, int citiesCount)
{
	int flights = 0;

	scanf("%d", &flights);
	getchar();

	while (flights)
	{
		char bfr[STRLEN];
		fgets(bfr, STRLEN, stdin);
		LiteString start = strtok(bfr, " ");
		char* dest = strtok(NULL, " ");
		int cost = atoi(strtok(NULL, " "));

		Cities* city = hashTable[generateHash(&start) % citiesCount]->findCity(&start);
		if (city)
		{
			if (!city->neighbors)
			{
				city->neighbors = new Neighborhood(LiteString(dest), cost);
				city->lastNeighbor = city->neighbors;
			}
			else
			{
				city->lastNeighbor->next = new Neighborhood(LiteString(dest), cost);
				city->lastNeighbor = city->lastNeighbor->next;
			}
		}
		flights--;
	}
}

void parseQueries(Nodes** hashTable, Cities* cities, int citiesCount)
{
	int queries = 0;

	scanf("%d", &queries);
	getchar();

	while (queries)
	{
		char bfr[STRLEN];
		fgets(bfr, STRLEN, stdin);
		LiteString start = strtok(bfr, " ");
		LiteString dest = strtok(NULL, " ");
		Cities* startCity = hashTable[generateHash(&start) % citiesCount]->findCity(&start);
		Cities* destCity = hashTable[generateHash(&dest) % citiesCount]->findCity(&dest);

		int printPath = atoi(strtok(NULL, " "));
		dijkstra(cities, startCity, destCity, citiesCount, hashTable, printPath);
		queries--;
	}
}

void deleteContents(Nodes** hashTable, Cities* cities, int citiesCount)
{
	Cities* first = cities;
	while (first != nullptr)
	{
		Cities* next = first->next;
		delete first;
		first = next;
	}

	for (int i = 0; i < citiesCount; i++)
		delete hashTable[i];
	delete[] hashTable;
}