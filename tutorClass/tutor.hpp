//Tutor Class header file
//Author: Mackenzie Zappe 
//Date Started: 11/19/2020
//Last Updated: 11/19/2020
#ifndef _TUTOR_H_
#define _TUTOR_H_


#include <string> 
#include <iostream>
#include <map>

#define NUM_DAYS 7

struct shift{ shift(): m_start(0), m_end(0) {}

    int m_start;
    int m_end;

    void printShift(){
        std::cout << "Start: " << m_start << " End: " << m_end << " \n";
    }
};


class Tutor{
    public:

    Tutor(){
        defaultSchedule();
        defaultAbilities();
    }

    Tutor(std::string tutorName, bool cleared, shift schedule[NUM_DAYS], std::map<std::string,bool> m):
    m_name(tutorName), m_cleared(cleared)
    {
        std::cout << "this is the param ctor " << m_name << m_cleared << std::endl;
        m_abilities = m;
    }

    Tutor(std::string tutorName, bool cleared, shift schedule[NUM_DAYS]):
    m_name(tutorName), m_cleared(cleared)
    {
        defaultAbilities();
    }
    Tutor(std::string tutorName, bool cleared):
    m_name(tutorName), m_cleared(cleared)
    {
        defaultSchedule();
        defaultAbilities();

    }

    void addShift(shift newshift, int index){
        m_schedule[index-1] = newshift;
        newshift.printShift();
    }

    void displaySchedule() {
        for(int i = 0; i < NUM_DAYS; i++){
            m_schedule[i].printShift();
        }
    }

    void defaultAbilities() {
        m_abilities["m095"] = false;
        m_abilities["m096"] = false;
        m_abilities["m120"] = false;
        m_abilities["m120E"] = false;
        m_abilities["m122"] = false;
        m_abilities["m123"] = false;
        m_abilities["m126"] = false;
        m_abilities["m126E"] = false;
        m_abilities["m127"] = false;
        m_abilities["m181"] = false;
        m_abilities["m182"] = false;
        m_abilities["m283"] = false;
        m_abilities["m285"] = false;
        m_abilities["m295"] = false;
        m_abilities["m330"] = false;
        m_abilities["s152"] = false;
        m_abilities["s352"] = false; 
    }
    void defaultSchedule() {
        shift emptyShift;
        for(int i = 0; i < NUM_DAYS; i++){
            m_schedule[i] = emptyShift;
        }
    }

    void printAbilities()
    {
        for (auto const& pair: m_abilities) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }

    void changeAbilities(std::string key, bool newValue){
        m_abilities.find(key) ->second = newValue;
    }

    private:
    std::string m_name;
    bool m_cleared;

    shift m_schedule[NUM_DAYS];
    std::map<std::string, bool> m_abilities;

};

#endif