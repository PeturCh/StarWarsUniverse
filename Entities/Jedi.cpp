#pragma once
#include "Jedi.h"

String Jedi::denormalizeName(String other)
{
    for (size_t i = 0; i < other.getLength(); i++)
    if (other[i] == '_')
        other[i] = ' ';
    return other; 
}

Jedi::Jedi() 
{
    name = "None";
    rang = (Rang)1;
    age = 50000;
    saberColour = "transperant";
    power = 0;
    planetName = "None";
}

Jedi::Jedi(const String &_name, const Rang &_rang, const usi &_age, const String &_saberColour, const double &_power, const String &_planetName)
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

Jedi::Jedi(const Jedi &other)
{
    name = other.name;
    rang = other.rang;
    age = other.age;
    saberColour = other.saberColour;
    power = other.power;
    planetName = other.planetName;
}

double Jedi::getPower()
{
    return power;
}

usi Jedi::getAge()
{
    return age;
}

char* Jedi::getName()
{
    char* nameArr = new char[name.getLength() + 1];
    for (size_t i = 0; i < name.getLength(); i++)
    {
        nameArr[i] = name[i];
    }
    nameArr[name.getLength()] = '\0';
    return nameArr;
}

usi Jedi::getRank()
{
    return rang;
}

String Jedi::getRankText(int add)
{
    String rankText;
    switch (rang + add)
    {
    case 1: rankText = "YOUNGLING";
        break;
    case 2: rankText = "INITIATE";
        break;
    case 3: rankText = "PADAWAN";
        break;
    case 4: rankText = "KNIGHT ASPIRANT";
        break;
    case 5: rankText = "KNIGHT";
        break;
    case 6: rankText = "MASTER";
        break;
    case 7: rankText = "BATTLE MASTER";
        break;
    case 8: rankText = "GRAND MASTER";
        break;
    
    default: 
        break;
    }
    return rankText;
}

char* Jedi::getSaberColour()
{
    char* saber = new char[saberColour.getLength() + 1];
    for (size_t i = 0; i < saberColour.getLength(); i++)
    {
        saber[i] = saberColour[i];
    }
    return saber;
}

void Jedi::print()
{
    String rankText;
    switch (rang)
    {
    case 1: rankText = "YOUNGLING";
        break;
    case 2: rankText = "INITIATE";
        break;
    case 3: rankText = "PADAWAN";
        break;
    case 4: rankText = "KNIGHT ASPIRANT";
        break;
    case 5: rankText = "KNIGHT";
        break;
    case 6: rankText = "MASTER";
        break;
    case 7: rankText = "BATTLE MASTER";
        break;
    case 8: rankText = "GRAND MASTER";
        break;
    
    default: 
        break;
    }
    std::cout << denormalizeName(name) << ' ' << "rank: " << rankText << ", " << age << " years old," << ' ' << saberColour << " saber" << ' ' << "with " << power << " power, from " << denormalizeName(planetName)<<'\n';
}

String Jedi::getSaberColour2()
{
    return saberColour;
}

String Jedi::getPlanet()
{
    return planetName;
}

Jedi& Jedi::operator=(const Jedi &other)
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
    
std::ostream& operator<<(std::ostream& out,  Jedi &j)
{   
    out << j.name << ' ' << j.rang << ' ' << j.age << ' ' << j.saberColour << ' ' << j.power << '\n';
    return out;
}

