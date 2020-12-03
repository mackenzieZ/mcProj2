//MCproj2 menu file

#include <iostream>
#include "tutor.hpp"

void displayMainMenu() {
    std::cout << "===MENU===" << std::endl;
    std::cout << "1) Tutor Information" << std::endl << "2) Course Information" << std::endl << "3) Generate Review" << std::endl << "0) Exit" << std::endl;
    std::cout << "Which menu option would you like to access?" << std::endl;
}

void tutorMenu(){
    std::cout << "===Tutor Information=== " << std::endl;
    std::cout << "1)Add Tutor" << std::endl << "2)Remove Tutor" << std::endl << "3) Edit Existing Tutor" << std::endl << "4) Load Schedule File" << std::endl << "0)Return to Main Menu" << std::endl;
    std::cout << "Which option would you like to access?" << std::endl;
}

void editTutorMenu(){
    std::cout << "===Edit Tutor===" << std::endl;
    std::cout << "1)Change their schedule" << std::endl << "2)Change their abilities" << std::endl << "0)Return to Tutor Information" << std::endl;
    std::cout << "Which option would you like to access?" << std::endl;
}

void abilitiesMenuOption(Tutor t1){
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
}

Shift * scheduleMenuOption(){
    Shift schedule[NUM_DAYS];
    for(int i = 0; i < NUM_DAYS; i++){
        Shift input;
        std::string start;
        std::string end;
        std::cout << "Start :";
        std::cin >> start;
        std::cout << "End: ";
        std::cin >> end;

        input.m_start = MCTime(start);
        input.m_start = MCTime(end);
        schedule[i] = input; 
    }
    return schedule;
}