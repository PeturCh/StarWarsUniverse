#pragma once
#include <iostream>
#include "string.h"


void String::copy(const String& other)
{
    capacity = other.capacity;
    length = other.length;
    data = new char[other.capacity];

    for(size_t i = 0; i < length; i++)
    {
        data[i] = other.data[i];
    }
}

void String::copy(const char* other)
{
    size_t _length = 0;
    for (size_t i = 0; other[i] != '\0'; i++)
    {
        _length++;
    }
    length = _length;
    capacity = _length + 1;
    data = new char[capacity];

    for(size_t i = 0; i < length; i++)
    {
        data[i] = other[i];
    }
}

void String::destroy()
{
    delete []data;
}

void String::resize()
{
    capacity += 8;
    char* newString = new char[capacity];
    for(usi i = 0; i < length; i++)
    {
        newString[i] = data[i];
    }
    destroy();
    data = newString;
}

void String::resize(usi size)
{
    capacity += size;
    char* newString = new char[capacity];
    for(usi i = 0; i < length; i++)
    {
        newString[i] = data[i];
    }
    destroy();
    data = newString;
}

String::String()
{
    capacity = 8;
    length = 0;
    data = new char[capacity];
}

String::String(const String& other)
{
    copy(other);
}

String::String(const char *other)
{
    copy(other);
}

String::String(const char other)
{
    copy(other);
}

//String::String(usi other)
//{
//    capacity = 8;
//    length = 0;
//    data = new char[capacity];
//
//    if(other > 9)
//    {
//        usi result = 0, remains;
//        while(other != 0) 
//        {
//            remains = other % 10; 
//            result = result*10 + remains; 
//            other /= 10; 
//        }
//        other = result;
//
//        while(other!=0)
//        {
//            this->push_back('0' + other % 10);
//            other /= 10;
//        }
//    }
//    else this->push_back('0' + other);
//
//}

String& String::operator=(const String& other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

String& String::operator=(const char *other)
{
    destroy();
    copy(other);
    return *this;
}

const bool String::operator==(const String& other)
{
    if(other.getLength() != this->getLength())
        return false;

    for (size_t i = 0; i < getLength(); i++)
    {
        if (data[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

String::~String()
{
    destroy();   
}

const bool String::isEmpty() const
{
    return length == 0;
}

usi String::getLength() const
{
    return length;
}

usi String::getCapacity() const
{
    return capacity;
}

char String::operator[](usi i) const
{
    if(i < length)
    {
        return data[i];
    }
    throw;
}

char& String::operator[](usi i)
{
    if(i < length)
    {
        return data[i];
    }
    throw;
}

void String::copyString(char target[], usi len, usi pos)
{
    for (usi i = pos, j = 0; i < pos + len; i++, j++)
    {
        target[j] = data[i];
    }
}

void String::shrink_to_fit()
{
    char *buffer = new char[length];
    destroy();
    data  = buffer;
}

void String::push_back(const char& newChar)
{
    if(length == capacity)
    {
        resize();
    }
    data[length++] = newChar;
}

void String::push_back(const char *newStr)
{
    usi size = 0;
    for (usi i = 0; newStr[i] != '\0'; i++)
    {
        size++;
    }
    
    if(length + size <= capacity)
    {
        resize(length + size - capacity + 1);
    }

    for (usi i = length, j = 0; i < length + size, j < size; i++, j++)
    {
        data[i] = newStr[j];
    }
}

void String::push_back(const String &other)
{
    
    if(length + other.length <= capacity)
    {
        resize(length + other.length - capacity + 1);
    }

    for (usi i = length, j = 0; i < length + other.length; i++, j++)
    {
        data[i] = other[j];
    }
}

//String String::push_back(const String other)
//{
//    if(length + other.length <= capacity)
//    {
//        resize(length + other.length - capacity + 1);
//    }
//
//    for (usi i = length, j = 0; i < length + other.length; i++, j++)
//    {
//        data[i] = other[j];
//    }
//
//    return other;
//}





/*
void String::pop_back()
{
    data[--length] = '\0';
}
*/
void String::swap(String other)
{
    String temp(other);
    other = *this;
    *this = temp;
}

std::ostream& operator<<(std::ostream& out, const String& current)
{
    for (size_t i = 0; i < current.getLength(); i++)
    {
        out << current.data[i];
    }
    
    //out << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, const String& current)
{
    for (size_t i = 0; i < current.getLength(); i++)
    {
        in >> current.data[i];
    }
    return in;
}