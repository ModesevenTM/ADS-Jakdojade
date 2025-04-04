#include "func.h"

int generateHash(LiteString* str)
{
	size_t len = str->getlen();
	switch (len)
	{
	case 1:
	{
		if ((*str)[0] <= '9')
			return (int)(*str)[0] - 47;
		return (int)(*str)[0] - 53;
	}
	case 2:
	{
		int hash = 0;
		if ((*str)[0] <= '9')
			hash += (int)(*str)[0] - 47;
		else hash += (int)(*str)[0] - 53;
		if ((*str)[1] <= '9')
			hash += ((int)(*str)[1] - 47) * 37;
		else hash += ((int)(*str)[1] - 53) * 37;
		return hash;
	}
	case 3:
	{
		int hash = 0;
		if ((*str)[0] <= '9')
			hash += (int)(*str)[0] - 47;
		else hash += (int)(*str)[0] - 53;
		if ((*str)[1] <= '9')
			hash += ((int)(*str)[1] - 47) * 37;
		else hash += ((int)(*str)[1] - 53) * 37;
		if ((*str)[2] <= '9')
			hash += ((int)(*str)[2] - 47) * 37 * 37;
		else hash += ((int)(*str)[2] - 53) * 37 * 37;
		return hash;
	}
	default:
	{
		int hash = 0;
		for (int i = 0; i < 2; i++)
		{
			if ((*str)[i] <= '9')
				hash += ((int)(*str)[i] - 47) * (int)pow(37, i);
			else
				hash += ((int)(*str)[i] - 53) * (int)pow(37, i);
			if ((*str)[len - i - 1] <= '9')
				hash += ((int)(*str)[len - i - 1] - 47) * (int)pow(37, 3 - i);
			else
				hash += ((int)(*str)[len - i - 1] - 53) * (int)pow(37, 3 - i);
		}
		return hash;
	}
	}
}

LiteString* checkForName(int x, int y, int maxX, char** map)
{
	if (map[y][x] >= '0')
	{
		if (x == 0 || (x > 0 && map[y][x - 1] < '0'))
		{
			int len = 0, i = x;
			while (map[y][i] >= '0')
			{
				len++;
				if (++i == maxX) break;
			}
			return new LiteString(&map[y][x], len);
		}
		else if (x == maxX - 1 || (x < maxX - 1 && map[y][x + 1] < '0'))
		{
			int len = 0, i = x;
			while (map[y][i] >= '0')
			{
				len++;
				if (--i < 0) break;
			}
			return new LiteString(&map[y][i + 1], len);
		}
	}
	return nullptr;
}

LiteString* findName(int x, int y, int maxX, int maxY, char** map)
{
	int dX;
	x == 0 ? dX = 0 : dX = x - 1;
	for (dX; (dX <= x + 1) && (dX < maxX); dX++)
	{
		int dY;
		y == 0 ? dY = 0 : dY = y - 1;
		for (dY; (dY <= y + 1) && (dY < maxY); dY++)
		{
			if (dX != x || dY != y)
			{
				LiteString* name = checkForName(dX, dY, maxX, map);
				if (name != nullptr)
					return name;
			}
		}
	}
	return nullptr;
}