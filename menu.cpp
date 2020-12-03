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
        std::cout << "What class would you like to enter abilities for (all abilities defaulted to false)? ";
        std::cin >> key;
        std::cout << "The current ability for this tutor for this class is: "  <<  std::endl; // add get abilities function
        std::cout << "Change abilities? yes capable - 1, not capable - 0 ";
        std::cin >>  change;
        t1.changeAbilities(key,change);
        std::cout << "Here are the abilities for " << t1.getName() << std::endl;
        t1.printAbilities();
        std::cout << "Would you like to continue entering abilities? 1- yes 0 - no" << std::endl;
        std::cin >> j;
    }while(j != 0);    
}

Shift * scheduleMenuOption(){
    
    Shift schedule[NUM_DAYS];
    for(int i = 0; i < NUM_DAYS; i++){
        MCTime start(hour_s, min_end);
        MCTime end(hour_e, min_e);

        std::cin >> hour_s, ;

        std::cin >> end;
        Shift input(start, end);
        schedule[i] = input; 
    }
    return schedule;
}