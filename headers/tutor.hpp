//Tutor Class header file
//Author: Mackenzie Zappe 
//Date Started: 11/19/2020
//Last Updated: 11/19/2020
#ifndef _TUTOR_H_
#define _TUTOR_H_

#include <string> 
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "MCTime.hpp"

#define NUM_DAYS 7

enum Employee_Type {TUTOR, FD};

// All shifts now represent a 30 min interval, a tutor has multiple shifts a day
struct Shift { 
    MCTime m_start;
    MCTime m_end;
    int m_day;

    Shift() : m_start(0), m_end(0), m_day(0) {}

    Shift(MCTime start, MCTime end, int day) : m_start(start), m_end(end), m_day(day) {};

    std::string to_string() const {
        return "Day:" + std::to_string(m_day) + " Start: " + m_start.to_string() + " End: " + m_end.to_string() ;
    }
    
    void printShift(){
        std::cout << to_string() << "\n";
    }
};

class Tutor {
    public:

    Tutor() {
        defaultSchedule();
        defaultAbilities();
    }

    Tutor(std::string tutorName, bool cleared, Shift schedule[NUM_DAYS], std::map<std::string,bool> m, Employee_Type type = Employee_Type::TUTOR):
    m_name(tutorName), m_cleared(cleared), m_type(type)
    {
        m_abilities = m;
        m_schedule = std::shared_ptr<std::vector<Shift>>(new std::vector<Shift>);
    }

    Tutor(std::string tutorName, bool cleared, Shift schedule[NUM_DAYS], Employee_Type type = Employee_Type::TUTOR):
    m_name(tutorName), m_cleared(cleared), m_type(type)
    {
        defaultAbilities();
        m_schedule = std::shared_ptr<std::vector<Shift>>(new std::vector<Shift>);
    }
    Tutor(std::string tutorName, bool cleared, Employee_Type type = Employee_Type::TUTOR):
    m_name(tutorName), m_cleared(cleared), m_type(type)
    {
        defaultSchedule();
        defaultAbilities();
        m_schedule = std::shared_ptr<std::vector<Shift>>(new std::vector<Shift>);
    }

    void addShift(Shift newshift){
        // m_schedule[index-1] = newshift;
        // newshift.printShift();
        m_schedule->push_back(newshift);
        std::cout << m_name << " Shift Added - " << newshift.to_string() << "\n"; 
    }

    void displaySchedule() {
        for (auto iterator = m_schedule->begin(); iterator != m_schedule->end(); iterator++)  {
            iterator->printShift();
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
        // Shift emptyShift;
        // for(int i = 0; i < NUM_DAYS; i++){
        //     m_schedule[i] = emptyShift;
        // }
    }

    //===== Functions to implement later ======
    //find tutor in list based on name
    

    void printAbilities()
    {
        for (auto const& pair: m_abilities) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }

    void changeAbilities(std::string key, bool newValue){
        m_abilities.find(key) ->second = newValue;
    }

    // Getters
    std::string getName() const { return m_name; }

    // Operators needed for compatibilty sake
    friend bool operator==(const Tutor & lhs, const Tutor & rhs);

    friend bool operator<(const Tutor & lhs, const Tutor & rhs);

    friend bool operator>(const Tutor & lhs, const Tutor & rhs);

    friend std::ostream & operator<<(std::ostream & os, const Tutor & tutor);

    private:
    std::string m_name;
    bool m_cleared;
    
    Employee_Type m_type;
    std::shared_ptr<std::vector<Shift>> m_schedule;
    std::map<std::string, bool> m_abilities;

};

std::ostream & operator<<(std::ostream & os, const Tutor & tutor) {
    os << tutor.m_name;
    return os;
}

bool operator==(const Tutor & lhs, const Tutor & rhs) {
    return lhs.m_name == rhs.m_name;
}

bool operator<(const Tutor & lhs, const Tutor & rhs) {
    return lhs.m_name < rhs.m_name;
}

bool operator>(const Tutor & lhs, const Tutor & rhs) {
    return lhs.m_name > rhs.m_name;
}

#endif