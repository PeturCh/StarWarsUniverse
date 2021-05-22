#include "..\Commands\commands.cpp"

//std::ifstream open(char *fileName)
//{
//    std::ifstream input(fileName);
//    return nullptr;
//}

int main()
{
    char command[20] = {'\0'};

    do
    {
        std::fill(std::begin(command), std::end(command), '\0');
        std::cout<<"\n> ";
        std::cin>>command;

        if(strcmp(command, "add_planet") == 0)
            {
                char planetName[50];
                std::cin>>planetName;
                std::cout<<planetName;
                add_planet(planetName);
            }

        else if(strcmp(command, "create_jedi") == 0)
            {
                char planetName[50], jediName[50], saberColour[50];
                usi rank, age;
                double power;
                std::cin>>planetName>>jediName>>rank>>age>>saberColour>>power;
                create_jedi(planetName,jediName,(Rang)rank,age,saberColour,power);
            }

        else if(strcmp(command, "remove_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                char planetName[50] = {'\0'};
                std::cin>>planetName>>jediName;
                remove_jedi(jediName, planetName);
            }

        else if(strcmp(command, "promote_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                double multipl;
                std::cin>>jediName>>multipl;
                remove_jedi(jediName, multipl);
            }

        else if(strcmp(command, "demote_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                double multipl;
                std::cin>>jediName>>multipl;
                remove_jedi(jediName, multipl);
            }

        else if(strcmp(command, "get_strongest_jedi") == 0)
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                get_strongest_jedi(planetName);
            }

        else if(strcmp(command, "get_youngest_jedi") == 0)
            {
                char planetName[50] = {'\0'};
                usi rank;
                std::cin>>planetName>>rank;
                get_youngest_jedi(planetName, rank);
            }

        else if(strcmp(command, "get_most_used_saber_color") == 0)
            {
                char planetName[50] = {'\0'};
                usi rank;
                std::cin>>planetName>>rank;
                get_most_used_saber_color(planetName, rank);
            }

        else if(strcmp(command, "get_most_used_saber_color") == 0)
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                get_most_used_saber_color(planetName);
            }

        else if(strcmp(command, "print_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                std::cin>>jediName;
                printJedi(jediName);
            }

        else if(strcmp(command, "print_planet") == 0)
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                printPlanet(planetName);
            }

        else 
        {
            char plananetName2[50], function;
            std::cin >> function;
            if(function == '+')
            {
                std::cin>>plananetName2;
                printJediFromPlanets(command, plananetName2);
            }
        }
        
    } while (strcmp(command, "Exit") != 0);
}
