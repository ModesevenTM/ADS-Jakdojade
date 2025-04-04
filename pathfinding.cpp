#include "pathfinding.h"


void bfs(Cities* city, char** map, int maxX, int maxY, int** weights) {
	int x = city->x;
	int y = city->y;
	coordQueue queue;
	queue.push(x, y);
	for (int t = 0; t < maxY; t++)
		for (int i = 0; i < maxX; i++)
			weights[t][i] = _MAX;
	weights[y][x] = 0;
	while (!queue.empty()) {
		intPair u = *(queue.front());
		queue.pop();
		if (map[u.y][u.x] == '*' && !(u.x == x && u.y == y)) {
			LiteString* name = findName(u.x, u.y, maxX, maxY, map);
			city->addNeighbor(name, weights[u.y][u.x]);
			delete name;

		}
		else {
			int coordX[4] = { 1, -1, 0, 0 };
			int coordY[4] = { 0, 0, 1, -1 };
			for (int i = 0; i < 4; i++) {
				int nx = u.x + coordX[i], ny = u.y + coordY[i];
				if (nx >= 0 && nx < maxX && ny >= 0 && ny < maxY && (map[ny][nx] == '#' || map[ny][nx] == '*') && weights[ny][nx] > weights[u.y][u.x] + 1) {
					weights[ny][nx] = weights[u.y][u.x] + 1;
					queue.push(nx, ny);
				}
			}
		}
	}
}

void printPath(Cities* end)
{
	if (end->prevOnPath)
	{
		strStack stack;
		Cities* city = end->prevOnPath;
		while (city->prevOnPath != nullptr)
		{
			stack.push(city->name);
			city = city->prevOnPath;
		}
		while (!stack.empty())
		{
			LiteString* current = stack.front();
			stack.pop();
			cout << " " << *current;
		}
	}
}


void dijkstra(Cities* front, Cities* start, Cities* end, int numCities, Nodes** hashTable, int path)
{
	for (Cities* city = front; city != nullptr; city = city->next)
	{
		city->distance = _MAX;
		city->visited = false;
		city->prevOnPath = nullptr;
	}

	start->distance = 0;
	PriorityQueue queue(numCities);
	queue.push(0, start);

	while (!queue.empty())
	{
		Cities* current = queue.pop();
		if (current->visited)
		{
			continue;
		}
		current->visited = true;

		if (current == end)
		{
			cout << end->distance;
			if (path) printPath(end);
			cout << endl;
			break;
		}

		for (Neighborhood* neighbor = current->neighbors; neighbor != nullptr; neighbor = neighbor->next)
		{
			Cities* neighborCity = hashTable[generateHash(&neighbor->name) % numCities]->findCity(&neighbor->name);
			if (!neighborCity->visited)
			{
				int distance = current->distance + neighbor->distance;
				if (distance < neighborCity->distance)
				{
					neighborCity->distance = distance;
					neighborCity->prevOnPath = current;
					queue.push(distance, neighborCity);
				}
			}
		}
	}
}