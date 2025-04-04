#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class LiteString {
private:
    char* str;
    size_t len;
public:
    LiteString();
    explicit LiteString(size_t size);
    LiteString(const char* in);
    LiteString(char* in);
    LiteString(const char* in, unsigned int len);
    LiteString(const LiteString& other);
    ~LiteString();
    LiteString& operator=(const LiteString& other);
    LiteString& operator=(const char* other);
    LiteString& operator+=(const LiteString& other);
    LiteString& operator+=(const char* other);
    bool operator==(const LiteString& other);
    bool operator==(const char* other);
    char& operator[](int index);
    const char& operator[](int index) const;
    size_t getlen() const;

    friend std::ostream& operator<<(std::ostream& ostr, const LiteString& str);
};