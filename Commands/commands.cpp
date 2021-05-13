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

bool jediExists(String jediName, String planetName = "")
{
    String jediNameNormalized = normalizeName(jediName);
    String planetNameNormalized = normalizeName(planetName);

    std::ifstream input("..\\Data\\new.txt");
    char nameFF[100];
    char planetFF[100];
    while(!input.eof())
    {   
        input >> nameFF;
        if (nameFF[0] == '-')
        {
            continue;
        }
        input >> planetFF;

        if (jediNameNormalized == nameFF && (planetNameNormalized == planetFF || planetName == ""))
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
    String normalizedName = normalizeName(name);
    std::ifstream input("..\\Data\\new.txt");
    char nameFF[100];
    while(!input.eof())
    {
        input >> nameFF;
        if(nameFF[0] != '-')
            continue;
        if (normalizedName == nameFF + 2)
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

    if(jediExists(jediName, planetName))
    {
        std::cout<<"There is already a jedi called " << jediName << " on planet " << planetName << "!" << '\n';
        return;
    }

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
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0)
    {
        std::cout<<"All changes are saved successfully in the file!\n";
    }
}

void remove_jedi(String jediName, String planetName)
{
    if(!jediExists(jediName, planetName))
    {
        std::cout<<"There is not such jedi!\n";
        return;
    }

    if(!planetExists(planetName))
    {
        std::cout<<"There is not such planet!\n";
        return;
    }

    std::ifstream input("..\\Data\\new.txt");
    std::ofstream output("..\\Data\\new2.txt" , std::fstream::app);
    char row[150];
    while(!input.eof())
    {
        input.getline(row , 150 , '\n');

        if (row[0] == '-')
        {
            output << row << '\n';
            continue;
        }

        String name;
        for (usi i = 0; row[i] != '\0'; i++)
        {
            if(row[i] == ' ') 
            {
                break;
            }
            name.push_back(row[i]);
        }

        
        if (!(normalizeName(jediName) == name))
        {
            output << row << '\n';
        }
    }

    output.close();
    input.close();
    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0)
    {
        std::cout<<"All changes are saved successfully in the file!\n";
    }
}
 
void promote_jedi(String jediName, double multipl)
{
    if(multipl <= 0)
    {  
        std::cout<<"You can not promote jedi with nonpositive number!\n";
        return;
    }

    if(!jediExists(jediName))
    {
        std::cout<<"There is not such jedi!\n";
        return;
    }
    String normalizedName = normalizeName(jediName);
    char nameFF[50], planetFF[50], colourFF[20];
    usi rangFF, ageFF;
    double powerFF;

    std::ifstream input("..\\Data\\new.txt");
    std::ofstream output("..\\Data\\new2.txt", std::fstream::app);

    while(!input.eof())
    {
        input >> nameFF;
        if(input.eof())
            break;

        if(nameFF[0] == '-')
        {
            output << nameFF << '\n';
            continue;
        }

        input >> planetFF >> rangFF >> ageFF >> colourFF >> powerFF;

        if(normalizedName == nameFF)
        {
            Jedi j(nameFF, (Rang) (rangFF+1), ageFF, colourFF, powerFF * multipl, planetFF);
            output << j;
            continue;
        }
        else 
        {
            Jedi j(nameFF, (Rang)rangFF, ageFF, colourFF, powerFF, planetFF);
            output << j;
            continue;
        }

    }
    output.close();
    input.close();
    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0)
    {
        std::cout<<"Jedi " <<jediName << " promoted successfully!\n";
    }
}

void demote_jedi(String jediName, double multipl)
{
    if(multipl <= 0)
    {  
        std::cout<<"You can not demote jedi with nonpositive number!\n";
        return;
    }

    if(!jediExists(jediName))
    {
        std::cout<<"There is not such jedi!\n";
        return;
    }
    String normalizedName = normalizeName(jediName);
    char nameFF[50], planetFF[50], colourFF[20];
    usi rangFF, ageFF;
    double powerFF;

    std::ifstream input("..\\Data\\new.txt");
    std::ofstream output("..\\Data\\new2.txt", std::fstream::app);
       
    while(!input.eof())
    {
        input >> nameFF;
        if(input.eof())
            break;

        if(nameFF[0] == '-')
        {
            output << nameFF << '\n';
            continue;
        }

        input >> planetFF >> rangFF >> ageFF >> colourFF >> powerFF;

        if(normalizedName == nameFF)
        {
            Jedi j(nameFF, (Rang) (rangFF-1), ageFF, colourFF, powerFF - powerFF * multipl, planetFF);
            output << j;
            continue;
        }
        else 
        {
            Jedi j(nameFF, (Rang)rangFF, ageFF, colourFF, powerFF, planetFF);
            output << j;
            continue;
        }

    }
    output.close();
    input.close();
    remove("..\\Data\\new.txt");
    if(rename("..\\Data\\new2.txt", "..\\Data\\new.txt") == 0)
    {
        std::cout<<"Jedi " <<jediName << " demoted successfully!\n";
    }

}
int main()
{
    //add_planet("Earth Second");
    //add_planet("Mars");
    //add_planet("Jupiter ohohoh");
    //add_planet("Mercury wowoow");

    //create_jedi("Earth Second", "Ango Ochite", (Rang)5, 24, "blue", 99.71);
    //create_jedi("Earth Second", "Peshko Beibe", (Rang)5, 19, "blue", 85.27);
    //create_jedi("Earth Second", "Georgi", (Rang)6, 57, "blue", 85.27);
    //create_jedi("Mars", "Ango Bango", (Rang)2, 18, "red", 59.12);
    //create_jedi("Jupiter ohohoh", "Vesko", (Rang)4, 21, "green", 87.75);
    //create_jedi("Jupiter ohohoh", "Angelcho", (Rang)4, 24, "bluee", 87.75);
    //create_jedi("Mercury wowoow", "Gosho", (Rang)1, 8, "purple", 12.45);

    promote_jedi("Georgi", 1.77);

}

