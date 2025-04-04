#pragma once
#include "commons.h"
#include "func.h"

class Cities;

class Nodes
{
public:
	Cities* first = nullptr;
	Cities* last = nullptr;

	Cities* findCity(LiteString* name);
};

class Neighborhood
{
public:
	LiteString name;
	int distance;
	Neighborhood* next = nullptr;

	Neighborhood(LiteString name, int distance);
};

class Cities
{
public:
	LiteString* name = nullptr;
	int x = -1, y = -1, hash = -1;
	Neighborhood* neighbors = nullptr;
	Neighborhood* lastNeighbor = nullptr;
	Cities* prevOnPath = nullptr;
	Cities* next = nullptr;
	Cities* nextHT = nullptr;
	bool visited = false;
	int distance = _MAX;

	Cities();
	Cities(int x, int y);
	~Cities();

	void addNeighbor(LiteString* cityName, int dist);
	void hashify(Nodes** hashTable, int elems);
};

class PriorityQueue
{
public:
	explicit PriorityQueue(int maxSize);
	PriorityQueue(const PriorityQueue& que);
	PriorityQueue& operator=(const PriorityQueue& que);
	~PriorityQueue();
	void push(int priority, Cities* city);
	Cities* pop();
	bool empty() const;

private:
	struct Item
	{
		int priority;
		Cities* city;
	};
	Item* heap;
	int maxSize;
	int size = 0;

	static int parent(int i);
	static int childLeft(int i);
	static int childRight(int i);
	void swap(int i, int j);
	void doubleCapacity();
};

class strContainer
{
public:
	LiteString* str;
	strContainer* prev = nullptr;
	strContainer* next = nullptr;

	explicit strContainer(LiteString* str);
};

class strStack
{
public:
	strContainer* first = nullptr;
	strContainer* last = nullptr;

	void push(LiteString* str);
	void pop();
	LiteString* front() const;
	bool empty() const;

	~strStack();
};

class intPair
{
public:
	int x, y;
	intPair* prev = nullptr;
	intPair* next = nullptr;

	intPair(int x, int y);
};

class coordQueue
{
public:
	intPair* first = nullptr;
	intPair* last = nullptr;

	void push(int x, int y);
	void pop();
	intPair* front() const;
	bool empty() const;

	~coordQueue();
};