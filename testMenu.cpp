//testing the main menu


#include <iostream>
#include "menu.cpp"

int  main(int argc, char ** argv) {
    int primaryChoice, secondaryChoice, terteraryChoice;

    do {
        displayMainMenu();
        std::cin >> primaryChoice;

        switch (primaryChoice) {
            case 1: {
                do {
                    tutorMenu();
                    std::cin >> secondaryChoice; 
                    switch(secondaryChoice){
                        case 1: {
                            std::string n_name;
                            std::string decision;
                            bool cleared;
                            std::cout << "New Name: ";
                            std::cin >> n_name;
                            std::cout << "Are they able to lead RS? 1 - yes, 0 - no ";
                            std::cin >> cleared;
                            std::cout << "Would you like to input their schedule or abilites at this time?'\n Please enter 'schedule', 'abilities', 'both' or 'neither' ";
                            std::cin >> decision;
                            if (decision == "schedule") {
                                shift schedule[NUM_DAYS];
                                for(int i = 0; i < NUM_DAYS; i++){
                                    shift input;
                                    std::cout << "Start :";
                                    std::cin >> input.m_start;
                                    std::cout << "End: ";
                                    std::cin >> input.m_end;
                                    schedule[i] = input; 
                                }
                                Tutor t1(n_name, cleared, schedule);
                            } else if(decision == "abilities") {
                                Tutor t1(n_name, cleared);
                                int j;
                                std::string key;
                                bool change;
                                do{
                                    std::cout << "What class would you like to enter abilities for(all abilities defaulted to false)? ";
                                    std::cin >> key;
                                    std::cout << "Change abilities? yes capable - 1, not capable - 0 ";
                                    std::cin >>  change;
                                    t1.changeAbilities(key,change);
                                    std::cout << "To end entering abilities enter 5 else press any number" << std::endl;
                                    std::cin >> j;
                                }while(j != 5);
                            } else if(decision == "both") {
                                //enter both
                            } else if(decision == "neither") {
                                Tutor t1(n_name, cleared);
                            }
                            std::cout << "Tutor added" << std::endl;
                        } break; //add tutor
                        case 2:{
                        } break; //remove tutor
                        case 3:{
                            do{
                                editTutorMenu();
                                std::cin >> terteraryChoice;
                                if(terteraryChoice == 1){
                                    //edit schedule
                                }else if(terteraryChoice == 2){
                                    //edit abilities
                                }else{
                                    std::cout << "Invalid entry" << std::endl;
                                }
                            }while(terteraryChoice != 0);
                        } break;
                        case 4: {

                        } break;
                    }
                } while(secondaryChoice != 0);
            } break;  
            case 2:{}break;
            case 3:{}break;
        }
    } while(primaryChoice != 0);
    

    return 0;
}