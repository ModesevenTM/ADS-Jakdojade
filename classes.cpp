#include "classes.h"

Cities* Nodes::findCity(LiteString* name)
{
	for (Cities* city = first; city != nullptr; city = city->nextHT)
	{
		if (*name == *city->name) return city;
	}
	return nullptr;
}

Neighborhood::Neighborhood(LiteString name, int distance)
	: name(name), distance(distance) {};

Cities::Cities() {};
Cities::Cities(int x, int y)
	: x(x), y(y) {};

Cities::~Cities()
{
	delete name;
	while (neighbors != nullptr)
	{
		Neighborhood* nextNbr = neighbors->next;
		delete neighbors;
		neighbors = nextNbr;
	}
}

void Cities::addNeighbor(LiteString* cityName, int dist)
{
	if (!neighbors)
	{
		neighbors = new Neighborhood(*cityName, dist);
		lastNeighbor = neighbors;
	}
	else
	{
		lastNeighbor->next = new Neighborhood(*cityName, dist);
		lastNeighbor = lastNeighbor->next;
	}
}

void Cities::hashify(Nodes** hashTable, int elems)
{
	hash = generateHash(name) % elems;
	if (hashTable[hash] == nullptr)
	{
		hashTable[hash] = new Nodes;
		hashTable[hash]->first = this;
		hashTable[hash]->last = this;
	}
	else
	{
		hashTable[hash]->last->nextHT = this;
		hashTable[hash]->last = hashTable[hash]->last->nextHT;
	}
}


PriorityQueue::PriorityQueue(int maxSize) 
	: maxSize(maxSize) {
		heap = new Item[maxSize];
	}

PriorityQueue::PriorityQueue(const PriorityQueue& que)
{
	maxSize = que.maxSize;
	size = que.size;
	heap = new Item[maxSize];
	for (int i = 0; i < size; i++)
		heap[i] = que.heap[i];
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& que)
{
	if (this == &que) return *this;
	if (heap) delete[] heap;
	maxSize = que.maxSize;
	size = que.size;
	heap = new Item[maxSize];
	for (int i = 0; i < size; i++)
		heap[i] = que.heap[i];
	return *this;
}

PriorityQueue::~PriorityQueue()
{
	delete[] heap;
}

void PriorityQueue::push(int priority, Cities* city)
{
	if (size == maxSize)
		doubleCapacity();
	int i = size++;
	heap[i].priority = priority;
	heap[i].city = city;
	while (i != 0 && heap[i].priority < heap[parent(i)].priority)
	{
		swap(i, parent(i));
		i = parent(i);
	}
}

Cities* PriorityQueue::pop()
{
	if (size)
	{
		Cities* city = heap[0].city;
		heap[0] = heap[--size];
		int i = 0;
		while (true)
		{
			int left = childLeft(i);
			int right = childRight(i);
			int smallest = i;
			if (left < size && heap[left].priority < heap[smallest].priority)
			{
				smallest = left;
			}
			if (right < size && heap[right].priority < heap[smallest].priority)
			{
				smallest = right;
			}
			if (smallest == i)
			{
				break;
			}
			swap(i, smallest);
			i = smallest;
		}
		return city;
	}
	return nullptr;
}

bool PriorityQueue::empty() const
{
	return size == 0;
}

int PriorityQueue::parent(int i)
{
	return (i - 1) / 2;
}

int PriorityQueue::childLeft(int i)
{
	return 2 * i + 1;
}

int PriorityQueue::childRight(int i)
{
	return 2 * i + 2;
}

void PriorityQueue::swap(int i, int j)
{
	Item temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

void PriorityQueue::doubleCapacity()
{
	Item* newHeap = new Item[2 * maxSize];
	for (int i = 0; i < maxSize; i++)
		newHeap[i] = heap[i];
	delete[] heap;
	heap = newHeap;
	maxSize *= 2;
}

strContainer::strContainer(LiteString* str) : str(str) {};

void strStack::push(LiteString* str)
{
	if (!last)
	{
		last = new strContainer(str);
		first = last;
	}
	else
	{
		first->prev = new strContainer(str);
		first->prev->next = first;
		first = first->prev;
	}
}

void strStack::pop()
{
	if (first)
	{
		if (first == last)
		{
			delete first;
			first = nullptr;
			last = nullptr;
		}
		else
		{
			strContainer* newFirst = first->next;
			delete first;
			first = newFirst;
			first->prev = nullptr;
		}
	}
}

LiteString* strStack::front() const
{
	return first->str;
}

bool strStack::empty() const
{
	return first == nullptr;
}

strStack::~strStack()
{
	while (last != nullptr)
	{
		strContainer* prev = last->prev;
		delete last;
		last = prev;
	}
}

intPair::intPair(int x, int y) : x(x), y(y) {};

void coordQueue::push(int x, int y)
{
	if (!first)
	{
		first = new intPair(x, y);
		last = first;
	}
	else
	{
		last->next = new intPair(x, y);
		last->next->prev = last;
		last = last->next;
	}
}

void coordQueue::pop()
{
	if (first)
	{
		if (first == last)
		{
			delete first;
			first = nullptr;
			last = nullptr;
		}
		else
		{
			intPair* newFirst = first->next;
			delete first;
			first = newFirst;
			first->prev = nullptr;
		}
	}
}

intPair* coordQueue::front() const
{
	return first;
}

bool coordQueue::empty() const
{
	return first == nullptr;
}

coordQueue::~coordQueue()
{
	while (first != nullptr)
	{
		intPair* next = first->next;
		delete first;
		first = next;
	}
}