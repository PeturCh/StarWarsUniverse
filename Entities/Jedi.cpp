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

    Jedi() 
    {
        name = "None";
        rang = (Rang)1;
        age = 50000;
        saberColour = "transperant";
        power = 0;
        planetName = "None";
    }
    
    Jedi(const String &_name, const Rang &_rang, const usi &_age, const String &_saberColour, const double &_power, const String &_planetName)
    {
        name = _name;

        if(_rang > 8)
            rang = (Rang)8;
        else if(_rang < 1)
            rang = (Rang)1;
        else rang = _rang;

        age = _age;
        saberColour = _saberColour;
        
        if(_power < 0)
            power = 0;
        else power = _power;

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

    double getPower()
    {
        return power;
    }

    usi getAge()
    {
        return age;
    }

    char* getName()
    {
        char* nameArr = new char[name.getLength() + 1];
        for (size_t i = 0; i < name.getLength(); i++)
        {
            nameArr[i] = name[i];
        }
        return nameArr;
    }

    usi getRank()
    {
        return rang;
    }

    char* getSaberColour()
    {
        char* saber = new char[saberColour.getLength() + 1];
        for (size_t i = 0; i < saberColour.getLength(); i++)
        {
            saber[i] = saberColour[i];
        }
        return saber;
    }

    String getSaberColour2()
    {
        return saberColour;
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

