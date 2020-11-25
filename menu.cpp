//MCproj2 menu file

#include <iostream>
#include "Tutor.hpp"

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