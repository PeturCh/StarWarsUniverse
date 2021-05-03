#pragma once
#include <iostream>
#include <fstream>
#include "..\Services\string.cpp"
#include "..\Entities\Jedi.cpp"
#include <filesystem>

String normalizeName(String name)
{
    for (size_t i = 0; i < name.getLength(); i++)
        if (name[i] == ' ')
            name[i] = '_';

    return name;    
}

bool jediExists(String jediName, String planetName)
{
    std::ifstream input("..\\Data\\jedi.txt");
    char nameFF[100];
    char planetFF[100];
    while(!input.eof())
    {
        input >> nameFF;
        input >> planetFF;
        if (jediName == nameFF /*&& planetName == planetFF*/)
        {
            input.close();
            return true;
        }
    }
    input.close();
    return false;
}

bool planetExists(String name)
{   
    std::ifstream input("..\\Data\\planets.txt");
    char nameFF[100];
    while(!input.eof())
    {
        input >> nameFF;
        if (name == nameFF)
        {
            input.close();
            return true;
        }
    }
    input.close();
    return false;
}

bool planetExists2(String name)
{   
    std::ifstream input("..\\Data\\new.txt");
    char nameFF[100];
    while(!input.eof())
    {
        input >> nameFF;
        if(nameFF[0] != '-')
            continue;
        if (name == nameFF + 2)
        {
            input.close();
            return true;
        }
    }
    input.close();
    return false;
}

void add_planet(String name)
{
    if (planetExists(normalizeName(name)))
    {
        std::cout<<"This planet already exists! Planet name:  " << name << '\n';
        return;
    }
    
    std::ofstream output("..\\Data\\planets.txt", std::ios::app);
    output << normalizeName(name) << '\n';
    output.close();
}

void add_planet2(String name)
{
    if (planetExists2(normalizeName(name)))
    {
        std::cout<<"This planet already exists! Planet name:  " << name << '\n';
        return;
    }
    
    std::ofstream output("..\\Data\\new.txt", std::ios::app);
    output << "--" <<normalizeName(name) << '\n';
    output.close();
}

void create_jedi(String planetName, String jediName, Rang rang, usi age, String saberColour, double power)
{
    if (!planetExists(normalizeName(planetName)))
    {
        std::cout<<"The jedi wasn't created since there isn't such a planet! Planet name: "<< planetName <<'\n';
        return;
    }

    //if(jediExists(normalizeName(jediName), normalizeName(planetName)));
    //{
    //    std::cout<<"There is already a jedi called " << jediName << " on planet " << planetName << "!" << '\n';
    //    return;
    //}

    Jedi j(normalizeName(jediName), rang, age, saberColour, power, normalizeName(planetName));

    std::ofstream output("..\\Data\\jedi.txt", std::ios::app);
    output << j ;
    output.close();
}

void create_jedi2(String planetName, String jediName, Rang rang, usi age, String saberColour, double power)
{
    if (!planetExists2(normalizeName(planetName)))
    {
        std::cout<<"The jedi wasn't created since there isn't such a planet! Planet name: "<< planetName <<'\n';
        return;
    }

    //if(jediExists(normalizeName(jediName), normalizeName(planetName)));
    //{
    //    std::cout<<"There is already a jedi called " << jediName << " on planet " << planetName << "!" << '\n';
    //    return;
    //}

    Jedi j(normalizeName(jediName), rang, age, saberColour, power, normalizeName(planetName));

    std::ofstream output("..\\Data\\new.txt", std::ios::app);
    std::ofstream output2("..\\Data\\new2.txt", std::ios::app);
    std::ifstream input("..\\Data\\new.txt");
    char nameFF[100];
    while(!input.eof())
    {
        input.getline(nameFF, 100, '\n');
        if (nameFF[0] == '-')
        {
            output2 << nameFF << '\n';
        }
        
        if(nameFF[0] != '-')
        {
            output2 << nameFF << '\n';
            continue;
        }

        if (normalizeName(planetName) == nameFF + 2)
        {
            output2 << j ;
        }
    }
    output.close();
    output2.close();
    input.close();

    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0);
    {
        std::cout<<"All changes are saved successfully in the file!\n";
    }
}

void remove_jedi(String jediName, String planetName)
{
    std::ifstream input("..\\Data\\new.txt");
    char row[150];
    while(!input.eof())
    {
        input.getline(row , 150 , '\n');

        String name;
        for (usi i = 0; row[i] != '\0'; i++)
        {
            if(row[i] == ' ') 
            {
                break;
            }
            name.push_back(row[i]);
        }

        //if (name[0] == '-')
        //{
        //    std::ofstream output("..\\Data\\new2.txt" , std::fstream::app);
        //    output << row << '\n';
        //    output.close();
        //    continue;
        //}
        
        if (!(normalizeName(jediName) == name))
        {
            std::ofstream output("..\\Data\\new2.txt" , std::fstream::app);
            output << row << '\n';
            output.close();
        }
    }

    input.close();
    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0);
    {
        std::cout<<"All changes are saved successfully in the file!\n";
    }

    //char jediFF[100], planetFF[100], saberFF[20];
    //double powerFF;
    //Rang rangFF;
    //usi ageFF;
//
    //std::ifstream input("..\\Data\\jedi.txt");
//
    //std::ofstream output("..\\Data\\jediNew.txt" , std::fstream::app);
    //char row[150];
//
    //while(!input.eof())
    //{
    //    input >> jediFF;
    //    input >> planetFF;
    //    if (!(jediName == jediFF) && !(planetName == planetFF))
    //    {
    //        input >> rangFF >> ageFF >> saberFF >> powerFF;
    //        Jedi j(jediFF, rangFF, ageFF, saberFF, powerFF, planetFF);
    //        output << j;
    //        //input.getline(row, 50, '\n');
    //        //output << jediFF << ' ' << planetFF << ' ' << row << '\n';
    //    }
    //}
    //output.close();
}

void remove_jedi2(String jediName, String planetName)
{
    std::ifstream input("..\\Data\\new.txt");

    char row[150];
    while(!input.eof())
    {
        input >> row;

        if(row[0] == '-')
        {
            std::ofstream output("..\\Data\\new2.txt" , std::fstream::app);
            output << row << '\n';
            output.close();
            continue;
        }

        if(!(normalizeName(jediName) == row))
        {
            std::ofstream output("..\\Data\\new2.txt" , std::fstream::app);
            output << row << '\n';
            output.close();
            continue;
        }
        //String name;
        //for (usi i = 0; row[i] != '\0'; i++)
        //{
        //    if(row[i] == ' ') 
        //    {
        //        break;
        //    }
        //    name.push_back(row[i]);
        //}
        //if (!(jediName == name)) 
        //{
        //    std::ofstream output("..\\Data\\jediNew.txt" , std::fstream::app);
        //    output << row << '\n';
        //    output.close();
        //}
    }

    input.close();
    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0);
    {
        std::cout<<"All changes are saved successfully in the file!\n";
    }
}


int main()
{
    add_planet2("Earth Second");
    add_planet2("Mars");
    add_planet2("Jupiter ohohoh");
    add_planet2("Mercury wowoow");


    //create_jedi2("Earth Second", "Ango Ochite", (Rang)5, 24, "blue", 99.71);
    //create_jedi2("Earth Second", "Peshko Beibe", (Rang)5, 19, "blue", 85.27);
    //create_jedi2("Earth Second", "Georgi", (Rang)6, 57, "blue", 85.27);
    //create_jedi2("Mars", "Ango Bango", (Rang)2, 18, "red", 59.12);
    //create_jedi2("Jupiter ohohoh", "Vesko", (Rang)4, 21, "green", 87.75);
    //create_jedi2("Jupiter ohohoh", "Angelcho", (Rang)4, 24, "bluee", 87.75);
    //create_jedi2("Mercury wowoow", "Gosho", (Rang)1, 8, "purple", 12.45);

    remove_jedi("Ango Ochite", "Earth Second");
}

