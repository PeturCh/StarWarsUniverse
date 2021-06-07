#include "..\Commands\commands.cpp"

void getHelp()
{
    std::cout<<"The following commands are supported:\n"
            <<"------------------------FILES------------------------"
            <<"\nopen <file>	            opens <file>\n"
            <<"\nclose			    closes currently opened file\n"
            <<"\nsave			    saves the currently open file\n"
            <<"\nsaveas <file>	            saves the currently open file in <file>\n"
            <<"\nhelp			    prints this information\n"
            <<"\nexit			    exists the program\n"
            <<"\n---------------------Jedi & Planets---------------------"
            <<"add_planet <planet name>\n"
            <<"\ncreate_jedi  <planet name> <jedi name> <rank> <age> <saber colour> <power>\n"
            <<"\nremove_jedi  <jedi name> <planet name>\n"
            <<"\npromote_jedi  <jedi name> <multiplier>\n"
            <<"\ndemote_jedi  <jedi name> <multiplier>\n"
            <<"\nget_strongest_jedi  <planet name>\n"
            <<"\nget_youngest_jedi  <planet name> <rank>\n"
            <<"\nget_most_used_saber_color  <planet name> <rank>\n"
            <<"\nget_most_used_saber_color  <planet name>\n"
            <<"\nprint_jedi  <jedi name>\n"
            <<"\nprint_planet  <planet name>\n"
            <<"\n<planet name> + <planet name>  prints jedi from both planets\n";
}

std::ifstream open(char *fileName)
{
    std::ifstream input(fileName);
    return nullptr;
}

int main()
{
    bool opened = false;
    Commands commands;
    char command[20] = {'\0'};

    do
    {
        std::fill(std::begin(command), std::end(command), '\0');
        std::cout<<"\n> ";
        std::cin>>command;
        
        if(strcmp(command, "exit") == 0)
            break;
        
        if(strcmp(command, "open") == 0)
        {   
            char fileName[50];
            std::cin>>fileName;
            commands.open(fileName);
            opened = true;
        }
            
        else if(strcmp(command, "save") == 0)
            std::cout<<"saveCalled\n";

        else if(strcmp(command, "saveas") == 0)
            std::cout<<"saveasCalled\n";

        else if(strcmp(command, "close") == 0)
            std::cout<<"closeCalled\n";

        else if(strcmp(command, "help") == 0)
            getHelp();

        else if(strcmp(command, "add_planet") == 0)
            {
                char planetName[50];
                std::cin>>planetName;
                commands.add_planet(planetName);
            }

        else if(strcmp(command, "create_jedi") == 0)
            {
                char planetName[50], jediName[50], saberColour[50];
                usi rank, age;
                double power;
                std::cin>>planetName>>jediName>>rank>>age>>saberColour>>power;
                commands.create_jedi(planetName,jediName,(Rang)rank,age,saberColour,power);
            }

        else if(strcmp(command, "remove_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                char planetName[50] = {'\0'};
                std::cin>>jediName>>planetName;
                commands.remove_jedi(jediName, planetName);
            }

        else if(strcmp(command, "promote_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                double multipl;
                std::cin>>jediName>>multipl;
                commands.promote_jedi(jediName, multipl);
            }

        else if(strcmp(command, "demote_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                double multipl;
                std::cin>>jediName>>multipl;
                commands.demote_jedi(jediName, multipl);
            }

        else if(strcmp(command, "get_strongest_jedi") == 0) 
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                Jedi strongest = commands.get_strongest_jedi(planetName);
                if(strcmp(strongest.getName(), "None") == 0)
                    std::cout<<"There are not any jedi on this planet!\n";
                else strongest.print();
            }

        else if(strcmp(command, "get_youngest_jedi") == 0) 
            {
                char planetName[50] = {'\0'};
                usi rank;
                std::cin>>planetName>>rank;
                Jedi youngest = commands.get_youngest_jedi(planetName, rank);

                if(strcmp(youngest.getName(), "None") == 0)
                    std::cout<<"There are not any jedi satisfying this filter on this planet!\n";
                else youngest.print();
            }

        else if(strcmp(command, "get_most_used_saber_color_byRank") == 0) 
            {
                char planetName[50] = {'\0'};
                usi rank;
                std::cin>>planetName>>rank;
                std::cout<<"The most used color on planet " << planetName << " is ";
                std::cout<<commands.get_most_used_saber_color(planetName, rank);
            }

        else if(strcmp(command, "get_most_used_saber_color") == 0) 
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                std::cout<<"The most used color on planet " << planetName << " is ";
                std::cout<<commands.get_most_used_saber_color(planetName);
            }

        else if(strcmp(command, "print_jedi") == 0)
            {
                char jediName[50] = {'\0'};
                std::cin>>jediName;
                commands.printJedi(jediName);
            }

        else if(strcmp(command, "print_planet") == 0)
            {
                char planetName[50] = {'\0'};
                std::cin>>planetName;
                commands.printPlanet(planetName);
            }

        else if(strcmp(command, "order66") == 0)
            {
                commands.order66(); 
            }

        else if(strcmp(command, "duel") == 0)
            {
                char jedi1Name[50] = {'\0'};
                char jedi2Name[50] = {'\0'};
                std::cin>>jedi1Name>>jedi2Name;
                commands.duel(jedi1Name,jedi2Name);
            }

        else 
        {
            char plananetName2[50], function;
            std::cin >> function;
            if(function == '+')
            {
                std::cin>>plananetName2;
                commands.printJediFromPlanets(command, plananetName2);
            }
            std::cin.ignore(256, '\n');
        }
        
    } while (strcmp(command, "exit") != 0);
}
