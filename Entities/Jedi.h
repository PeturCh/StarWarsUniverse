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

    String denormalizeName(String other);

    public:

    Jedi();
    
    Jedi(const String &, const Rang &, const usi &_ge, const String &, const double &, const String &);

    Jedi(const Jedi &other);

    double getPower();

    usi getAge();

    char* getName();

    usi getRank();

    String getRankText(int add = 0);

    char* getSaberColour();

    void print();

    String getSaberColour2();

    String getPlanet();

    Jedi& operator=(const Jedi &other);

    friend std::ostream& operator<<(std::ostream& out, Jedi &j);
};