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
    Planet();

    Planet(String);

    Planet(const Planet&);

    Planet& operator=(const Planet&);

    String getName();
};