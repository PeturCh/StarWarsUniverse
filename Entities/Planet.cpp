#pragma once
#include <iostream>
#include "Jedi.cpp"
#include "..\Services\string.cpp"
#include "..\Services\Vector.cpp"

class Planet
{
    private:
    String name;
    Vector<Jedi> jedi;

    public:
    Planet() {}

    Planet(String _name)
    {
        name = _name;
    }

    Planet(const Planet &other)
    {
        name = other.name;
        jedi = other.jedi;
    }

    Planet& operator=(const Planet &other)
    {
        if(this != &other) 
        {
            name = other.name;
            jedi = other.jedi;
        }
        return *this;
    }

    String getName()
    {
        return name;
    }

};