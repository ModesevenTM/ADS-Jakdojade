#include "litestring.h"

LiteString::LiteString()
{
	len = 0;
	str = nullptr;
}

LiteString::LiteString(size_t size)
{
	len = size;
	str = new char[len + 1];
}

LiteString::LiteString(const char* in)
{
	len = strlen(in);
	str = new char[len + 1];
	strcpy(str, in);
}

LiteString::LiteString(char* in)
{
	len = strlen(in);
	str = new char[len + 1];
	strcpy(str, in);
}

LiteString::LiteString(const char* in, unsigned int len)
{
	this->len = len;
	str = new char[len + 1];
	memcpy(str, in, len);
	str[len] = '\0';
}

LiteString::LiteString(const LiteString& other)
{
	len = other.len;
	str = new char[len + 1];
	strcpy(str, other.str);
}

LiteString::~LiteString()
{
	delete[] str;
}

LiteString& LiteString::operator=(const LiteString& other)
{
	if (this == &other) return *this;
	delete[] str;
	len = other.len;
	str = new char[len + 1];
	strcpy(str, other.str);
	return *this;
}

LiteString& LiteString::operator=(const char* other)
{
	delete[] str;
	len = strlen(other);
	str = new char[len + 1];
	strcpy(str, other);
	return *this;
}

LiteString& LiteString::operator+=(const LiteString& other)
{
	char* temp = new char[len + other.len + 1];
	if (str)
	{
		strcpy(temp, str);
		delete[] str;
	}
	strcpy(temp + len, other.str);
	len += other.len;
	str = temp;
	return *this;
}

LiteString& LiteString::operator+=(const char* other)
{
	char* temp = new char[len + strlen(other) + 1];
	if (str)
	{
		strcpy(temp, str);
		delete[] str;
	}
	strcpy(temp + len, other);
	len += strlen(other);
	str = temp;
	return *this;
}

bool LiteString::operator==(const LiteString& other)
{
	if(str && other.str) return !strcmp(str, other.str);
	return false;
}

bool LiteString::operator==(const char* other)
{
	if(str && other) return !strcmp(str, other);
	return false;
}

char& LiteString::operator[](int index)
{
	return str[index];
}

const char& LiteString::operator[](int index) const
{
	return str[index];
}

size_t LiteString::getlen() const
{
	return len;
}

std::ostream& operator<<(std::ostream& ostr, const LiteString& str)
{
	ostr << str.str;
	return ostr;
}