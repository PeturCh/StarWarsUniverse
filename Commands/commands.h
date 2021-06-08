#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include "..\Services\string.cpp"
#include "..\Services\Dictionary.cpp"
#include "..\Entities\Jedi.cpp"
#include "..\Entities\Planet.cpp"

class Commands
{
    private:
    char fileName[100];

    Jedi getJedi(String );

    String normalizeName(String );

    Vector<Jedi> getJediFromPlanet(String );

    bool jediExists(String, String planetName = "");

    bool planetExists(String );

    public:
    Commands();

    void open(char[]);

    void add_planet(String);

    void create_jedi(String, String, Rang, usi, String, double);

    void remove_jedi(String, String);

    void promote_jedi(String, double);

    void demote_jedi(String, double);

    Jedi get_strongest_jedi(String);

    Jedi get_youngest_jedi(String, usi);

    String get_most_used_saber_color(String, usi);

    String get_most_used_saber_color(String);

    void printPlanet(String);

    void printJedi(String);

    void printJediFromPlanets(String, String);

    void duel(String, String);

    void order66();
};