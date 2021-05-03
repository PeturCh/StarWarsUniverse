#pragma once
#include <iostream>
#include "..\Services\string.cpp"
#include "..\Services\Vector.cpp"

using usi = unsigned short int;

enum Rang
{
    YOUNGLING = 1, INITIATE = 2, PADAWAN = 3, KNIGHT_ASPIRANT = 4, KNIGHT = 5, MASTER = 6, BATTLE_MASTER = 7, GRAND_MASTER = 8
};

class Jedi
{
    private:

    String name;
    Rang rang;
    usi age;
    String saberColour;
    double power;
    String planetName;

    public:

    Jedi() {}
    
    Jedi(const String &_name, const Rang &_rang, const usi &_age, const String &_saberColour, const double &_power, const String &_planetName)
    {
        name = _name;
        rang = _rang;
        age = _age;
        saberColour = _saberColour;
        power = _power;
        planetName = _planetName;
    }

    Jedi(const Jedi &other)
    {
        name = other.name;
        rang = other.rang;
        age = other.age;
        saberColour = other.saberColour;
        power = other.power;
        planetName = other.planetName;
    }

    Jedi& operator=(const Jedi &other)
    {
        if(this != &other)
        {
            name = other.name;
            rang = other.rang;
            age = other.age;
            saberColour = other.saberColour;
            power = other.power;
            planetName = other.planetName;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, Jedi &j);
};
    
std::ostream& operator<<(std::ostream& out,  Jedi &j)
{   
    out << j.name << ' ' << j.planetName << ' ' << j.rang << ' ' << j.age << ' ' << j.saberColour << ' ' << j.power << '\n';
    return out;
}

