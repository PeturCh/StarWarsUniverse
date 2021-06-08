#pragma once
#include "Planet.h"

Planet::Planet(){}

Planet::Planet(String _name)
{
    name = _name;
}

Planet::Planet(const Planet &other)
{
    name = other.name;
    jedi = other.jedi;
}

Planet& Planet::operator=(const Planet &other)
{
    if(this != &other) 
    {
        name = other.name;
        jedi = other.jedi;
    }
    return *this;
}

String Planet::getName()
{
    return name;
}
