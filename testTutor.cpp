#include <iostream>
#include <string>

#include "tutor.hpp"

using namespace std;

int main()
{
    std::cout << "Test" << std::endl;
    shift schedule[7];
    
    
    shift s1;
    s1.m_start = 12;
    s1.m_end = 4;

    s1.printShift();

    schedule[1] = s1;
    Tutor t0; 
    map<string, bool> abilities;
    abilities["m123"] = true;
    Tutor t1("Kenzie", true, schedule);
    Tutor t2;


    map<string,bool>::iterator it = abilities.find("m123");
    if (it != abilities.end()){
        it->second = false;
    }

    t1.printAbilities();

    t1.changeAbilities("m095", true);

    t1.printAbilities();

return 0;
}
