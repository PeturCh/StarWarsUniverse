#pragma once
#include "commands.h"

Jedi Commands::getJedi(String jediName)
{
    String jediNameNormalized = normalizeName(jediName);
    String planetFF;
    char nameFF[100];
    char buffer[200];
    std::ifstream input("..\\Data\\new.txt");
    while(!input.eof())
    {   
        input >> nameFF;
        if(input.eof())
            break;
        if (nameFF[0] == '-')
        {
            planetFF = nameFF + 2;
            continue;
        }
        if (jediNameNormalized == nameFF)
        {
            char colourFF[20];
            usi rangFF, ageFF;
            double powerFF;
            input >> rangFF >> ageFF >> colourFF >> powerFF;
            Jedi j(nameFF, (Rang)rangFF, ageFF, colourFF, powerFF, planetFF);
            input.close();
            return j;
        }
        input.getline(buffer, 200, '\n');
    }
    std::cout << "Jedi " << jediName << " doesn't exists!\n";
    input.close();
    return Jedi();
}

String Commands::normalizeName(String name)
{
    for (size_t i = 0; i < name.getLength(); i++)
        if (name[i] == ' ')
            name[i] = '_';
    return name;    
}

Vector<Jedi> Commands::getJediFromPlanet(String planetName)
    {
        String normalizedName = normalizeName(planetName);
        std::ifstream input("..\\Data\\new.txt");
        Vector<Jedi> jediFromPlanet;
        char buffer[150];
        char first[50];
        while(!input.eof())
        {
            input >> first;
            if(first[0] == '-')
            {
                if(normalizedName == first + 2)
                {
                    char nameFF[50], colourFF[20];
                    String planetFF = first + 2;
                    usi rangFF, ageFF;
                    double powerFF;
                    while(true)
                    {
                        input >> nameFF >> rangFF >> ageFF >> colourFF >> powerFF;
                        if(nameFF[0] != '-' && !input.eof())
                        {
                            Jedi j(nameFF, (Rang)rangFF, ageFF, colourFF, powerFF, planetFF);
                            jediFromPlanet.push_back(j);
                        }
                        else break;
                    }
                    break;
                }
                continue;
            }
            else input.getline(buffer, 150, '\n');
        }
        input.close();
        return jediFromPlanet;
    }

bool Commands::jediExists(String jediName, String planetName)
    {
        String jediNameNormalized = normalizeName(jediName);
        String planetNameNormalized = normalizeName(planetName);

        std::ifstream input("..\\Data\\new.txt");
        char nameFF[100];
        String planetFF;
        while(!input.eof())
        {
            input >> nameFF;
            if (nameFF[0] == '-')
            {
                planetFF = nameFF + 2;
                continue;
            }

            if (jediNameNormalized == nameFF && (planetNameNormalized == planetFF || planetName == ""))
            {
                input.close();
                return true;
            }
        }
        input.close();
        return false;
    }

bool Commands::planetExists(String name)
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

Commands::Commands(){}

void Commands::open(char _fileName[])
{
    strcpy(fileName, _fileName);
}

void Commands::add_planet(String name)
    {
        if (planetExists(normalizeName(name)))
        {
            std::cout<<"This planet already exists! Planet name:  " << name << '\n';
            return;
        }

        std::ofstream output("..\\Data\\new.txt", std::ios::app);
        output << "--" << normalizeName(name) << '\n';
        output.close();
        std::cout<<"Planet added successfuly! Planet name:  " << name << '\n';
    }

void Commands::create_jedi(String planetName, String jediName, Rang rang, usi age, String saberColour, double power)
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
        std::cout<<"Jedi added successfuly! Jedi name:  " << jediName << '\n';
    }
}

void Commands::remove_jedi(String jediName, String planetName)
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
            std::cout<<"Jedi " << jediName << " removed successfuly!\n";
        }
    }

void Commands::promote_jedi(String jediName, double multipl)
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
        char nameFF[50], colourFF[20];
        String planetFF;
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
                planetFF = nameFF + 2;
                continue;
            }

            input >> rangFF >> ageFF >> colourFF >> powerFF;

            if(normalizedName == nameFF)
            {
                Jedi j(nameFF, (Rang) (rangFF+1), ageFF, colourFF, powerFF + powerFF * multipl, planetFF);
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

void Commands::demote_jedi(String jediName, double multipl)
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
        char nameFF[50], colourFF[20];
        String planetFF;
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
                planetFF = nameFF + 2;
                continue;
            }

            input >> rangFF >> ageFF >> colourFF >> powerFF;

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

Jedi Commands::get_strongest_jedi(String planetName)
{
    Jedi strongest;
    if(planetExists(planetName))
    {
        Vector<Jedi> jediFromPlanet = getJediFromPlanet(planetName);
        for (usi i = 0; i < jediFromPlanet.getSize(); i++)
        {
            if(jediFromPlanet[i].getPower() > strongest.getPower())
                strongest = jediFromPlanet[i];
        }
    }
    else
        std::cout<<"There is not such planet!\n";
    return strongest;
}

Jedi Commands::get_youngest_jedi(String planetName, usi rank)
{   
    Jedi youngest;
    if(planetExists(planetName))
    {
        Vector<Jedi> jediFromPlanet = getJediFromPlanet(planetName);

        for (usi i = 0; i < jediFromPlanet.getSize(); i++)
        {
            if(jediFromPlanet[i].getAge() <= youngest.getAge() && jediFromPlanet[i].getRank() == rank)
            {
                if (jediFromPlanet[i].getAge() == youngest.getAge())
                {
                    if(strcmp(jediFromPlanet[i].getName(), youngest.getName()) < 0)
                        youngest = jediFromPlanet[i];
                    continue;
                }
                youngest = jediFromPlanet[i];
            }
        }
    }
    else
        std::cout<<"There is not such planet!\n";
    return youngest;
}

String Commands::get_most_used_saber_color(String planetName, usi rank)
{
    Vector<Jedi> jediFromPlanet = getJediFromPlanet(planetName);
    Vector<DictionaryPair<String,usi>> colours;
    bool containsColour = false;
    for (usi i = 0; i < jediFromPlanet.getSize(); i++)
    {
        if(jediFromPlanet[i].getRank() == rank)
        {
            for (usi j = 0; j < colours.getSize(); j++)
            {
                if(jediFromPlanet[i].getSaberColour2() == colours[j].getKey())
                {
                    colours[j].setValue(colours[j].getValue() + 1);
                    containsColour = true;
                }
            }
            if (!containsColour)
            {
                colours.push_back(DictionaryPair<String, usi>(jediFromPlanet[i].getSaberColour2(), 1));
            }
        }
        containsColour = false;
    }
    usi mostOccurrences = 0;
    String mostUsedColour;
    for (usi i = 0; i < colours.getSize(); i++)
    {
        if(colours[i].getValue() > mostOccurrences)
        {
            mostUsedColour = colours[i].getKey();
            mostOccurrences = colours[i].getValue();
        }
    }
    if(mostUsedColour.isEmpty())
    {
        std::cout<<"There is no jedi with this rank on planet "<< planetName << "\n";
    }
    return mostUsedColour;
}

String Commands::get_most_used_saber_color(String planetName)
    {
        std::ifstream input("..\\Data\\new.txt");

        Vector<Jedi> jediFromPlanet = getJediFromPlanet(planetName);

        Vector<DictionaryPair<String, usi>> colours;
        bool containsColour = false;

        for(usi i = 0; i < jediFromPlanet.getSize(); i++)
        {
            for (usi j = 0; j < colours.getSize(); j++)
            {
                if(jediFromPlanet[i].getSaberColour2() == colours[j].getKey())
                {
                    if(jediFromPlanet[i].getRank() == 8)
                        colours[j].setGMColour();
                    colours[j].setValue(colours[j].getValue() + 1);
                    containsColour = true;
                }
            }
            if (!containsColour)
            {
                if(jediFromPlanet[i].getRank() == 8)
                    colours.push_back(DictionaryPair<String, usi>(jediFromPlanet[i].getSaberColour2(), 1, true));

                else colours.push_back(DictionaryPair<String, usi>(jediFromPlanet[i].getSaberColour2(), 1));
            }
            containsColour = false;
        }

        usi mostOccurrences = 0;
        String mostUsedColour;

        for (usi i = 0; i < colours.getSize(); i++)
        {
            if(!colours[i].isGMColour())
                continue;

            if(colours[i].getValue() > mostOccurrences)
            {
                mostUsedColour = colours[i].getKey();
                mostOccurrences = colours[i].getValue();
            }
        }

        if(mostUsedColour.isEmpty())
        {
            std::cout<<"There is no jedi with rank GRAND MASTER on planet "<< planetName << "\n";
        }

        return mostUsedColour;
    }

void Commands::printPlanet(String planetName)
{
    if(!planetExists(planetName))
    {
        std::cout<<"There is not such planet!\n";
        return;
    }
    Vector<Jedi> jediFromPlanet = getJediFromPlanet(planetName);
    for(usi i = 0; i < jediFromPlanet.getSize(); i++)
        for (size_t j = i; j < jediFromPlanet.getSize(); j++)
            if(jediFromPlanet[i].getRank() > jediFromPlanet[j].getRank())
            {
                Jedi temp(jediFromPlanet[i]);
                jediFromPlanet[i] = jediFromPlanet[j];
                jediFromPlanet[j] = temp;
            }
    for (usi i = 0; i < jediFromPlanet.getSize(); i++)
        for (size_t j = i; j < jediFromPlanet.getSize(); j++)
            if(jediFromPlanet[i].getRank() == jediFromPlanet[j].getRank()) //only if the rank is the same
                if(std::strcmp(jediFromPlanet[i].getName(), jediFromPlanet[j].getName()) > 0) //only if the first jedi has alphabetically higher value
                {
                    Jedi temp(jediFromPlanet[i]);
                    jediFromPlanet[i] = jediFromPlanet[j];
                    jediFromPlanet[j] = temp;
                }
    if (jediFromPlanet.isEmpty())
    {
        std::cout<<"There are not any jedi on this planet!\n";
    }
    for (size_t i = 0; i < jediFromPlanet.getSize(); i++)
        jediFromPlanet[i].print();
}

void Commands::printJedi(String jediName)
    {
        Jedi j = getJedi(jediName);
        if(j.getName() != "None")
            j.print();
    }

void Commands::printJediFromPlanets(String planet1Name, String planet2Name)
    {
        Vector<Jedi> jediFromPlanet1 = getJediFromPlanet(planet1Name);
        Vector<Jedi> jediFromPlanet2 = getJediFromPlanet(planet2Name);

        usi planet1JediCount = jediFromPlanet1.getSize();
        usi planet2JediCount = jediFromPlanet2.getSize();

        Vector<Jedi> allJedi;

        for (usi i = 0; i < planet1JediCount + planet2JediCount; i++)
        {
            if(i < planet1JediCount)
                allJedi.push_back(jediFromPlanet1[i]);
            else allJedi.push_back(jediFromPlanet2[i-planet1JediCount]);
        }

        for (size_t i = 0; i < allJedi.getSize(); i++)
            for (size_t j = i; j < allJedi.getSize(); j++)
                if(strcmp(allJedi[i].getName(), allJedi[j].getName()) > 0)
                {
                    Jedi temp(allJedi[i]);
                    allJedi[i] = allJedi[j];
                    allJedi[j] = temp;
                }

        if (allJedi.isEmpty())
        {
            std::cout<<"There are not any jedi on these planets!\n";
        }

        for (size_t i = 0; i < allJedi.getSize(); i++)
            allJedi[i].print();

    }

void Commands::duel(String jedi1Name, String jedi2Name)
    {
        Jedi j1 = getJedi(jedi1Name);
        Jedi j2 = getJedi(jedi2Name);
        if(j1.getName() == "None" || j2.getName() == "None")
            return;

        if (j1.getPower() >= j2.getPower())
        {
            std::cout<<"What a glorious duel!\nThe winner is ... " << j1.getName() << '\n';
            int diff = j2.getRank() - j1.getRank();
            if(diff > 0)
            {
                promote_jedi(j1.getName(), diff * 0.5);
                std::cout<<"And he was promoted into " << j1.getRankText(1) << "!\n";
            }
            remove_jedi(j2.getName(), j2.getPlanet());
        }
        else
        {
            std::cout<<"What a glorious duel!\n The winner is ... " << j2.getName() << '\n';
            int diff = j1.getRank() - j2.getRank();
            if(diff > 0)
            {
                promote_jedi(j2.getName(), diff * 0.5);
                std::cout<<"And he was promoted into " << j2.getRankText(1) << "!\n";
            }
            remove_jedi(j1.getName(), j1.getPlanet());
        }
        
    }

void Commands::order66()
    {
        Vector<Planet> planets;
        char line[50];
        char buffer[150];
        std::ifstream input("..\\Data\\new.txt");
        
        while(!input.eof())
        {
            if(input.eof())
                break;

            input >> line;

            if (line[0] == '-')
            {
                planets.push_back(Planet(line+2));
            }
            else input.getline(buffer, 150, '\n');
        }
        input.close();

        for (size_t i = 0; i < planets.getSize(); i++)
        {
            Vector<Jedi> jedi = getJediFromPlanet(planets[i].getName());
            for (size_t j = 0; j < jedi.getSize(); j++)
            {
                if(strcmp(jedi[j].getName(), "Yoda") != 0)
                    remove_jedi(jedi[j].getName(), planets[i].getName());
            }
        }
    }

int main1()
{
    //add_planet("Earth Second");
    //add_planet("Mars");
    //add_planet("Jupiter o");
    //add_planet("Mercury w");
    //add_planet("Mars Bate");
    //add_planet("Saturn Shh");
//
//
    //create_jedi("Earth Second", "Ango Ochite", (Rang)5, 24, "blue", 99.71);
    //create_jedi("Earth Second", "Peshko Beibe", (Rang)5, 19, "blue", 85.27);
    //create_jedi("Earth Second", "Georgi", (Rang)6, 57, "blue", 39.27);
    //create_jedi("Saturn Shh", "Georgito", (Rang)7, 57, "green", 25.27);
    //create_jedi("Saturn Shh", "Georgidd", (Rang)8, 57, "red", 98.27);
    //create_jedi("Saturn Shh", "Vanio", (Rang)3, 5, "yellow", 85.27);
    //create_jedi("Mars", "Ango Bango", (Rang)2, 18, "red", 65.12);
    //create_jedi("Mars", "Ango Ghh", (Rang)8, 25, "blue", 80.12);
    //create_jedi("Mars Bate", "Peshko Marsa", (Rang)8, 18, "black", 65.12);
    //create_jedi("Jupiter o", "Vesko", (Rang)4, 21, "green", 32.75);
    //create_jedi("Jupiter o", "Angelcho", (Rang)4, 24, "bluee", 87.75);
    //create_jedi("Mercury w", "Gosho", (Rang)1, 8, "purple", 12.45);

    //remove_jedi("Georgidd", "Saturn Shh");

    //Jedi jj = get_strongest_jedi("Mercury_w");
    //std::cout<<jj << '\n';

    //Jedi j(get_youngest_jedi("Saturn Shh", 5));
    //std::cout << j<< '\n';

    //std::cout << get_most_used_saber_color("Saturn Shh", 5);

    //std::cout << get_most_used_saber_color("Earth Second");

    //printPlanet("Earth Second");

    //printJedi("Vanio");

    //printJediFromPlanets("Mars", "Earth Second");
    return 0;
}

