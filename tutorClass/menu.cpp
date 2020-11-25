//MCproj2 menu file

#include <iostream>
#include "tutor.hpp"

using namespace std;

void displayMainMenu(){
    cout << "===MENU===" << endl;
    cout << "1)Tutor Information" << endl << "2)Course Information" << endl << "3)Generate Review" << endl << "0)Exit" << endl;
    cout << "Which menu option would you like to access?" << endl;
}

void tutorMenu(){
    cout << "===Tutor Information=== " << endl;
    cout << "1)Add Tutor" << endl << "2)Remove Tutor" << endl << "3)Edit Existing Tutor" << endl << "0)Return to Main Menu" << endl;
    cout << "Which option would you like to access?" << endl;
}

void editTutorMenu(){
    cout << "===Edit Tutor===" << endl;
    cout << "1)Change their schedule" << endl << "2)Change their abilities" << endl << "0)Return to Tutor Information" << endl;
    cout << "Which option would you like to access?" << endl;
}