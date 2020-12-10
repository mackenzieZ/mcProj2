#pragma once

#include <iostream>
#include <sstream>
#include <string>

struct MCTime {
    int m_hour;
    int m_min;

    // Constructor that takes in an hour and a minute
    MCTime(int hour, int min) : m_hour(hour), m_min(min) {};
    // Constructor that takes in a time string like 3:20
    MCTime(std::string time_string) {
        if (time_string.find(':') == std::string::npos) {
            m_hour = std::stoi(time_string);
            m_min = 0;
        }
        else {
            std::istringstream ss(time_string);

            std::string token;
            std::getline(ss, token, ':');
            std::cout << token << "\n";
            m_hour = std::stoi(token);

            std::getline(ss, token, ':');
            std::cout << token << "\n";
            m_min = std::stoi(token);
        }
    };
    
    std::string to_string() const {
        return std::to_string(m_hour) + ":" + std::to_string(m_min);
    }

    MCTime next() {
        return m_min < 30 ? MCTime(m_hour, 30) : MCTime(m_hour + 1, 0);
    }

    MCTime am() {
        return *this;
    }

    MCTime pm() {
        return add(12, 0);
    }

    MCTime add(int hr, int min) {
        int newHr = m_hour + hr;
        int newMin = m_min + min;
        
        if (newMin >= 60) {
            newMin -= 60;
            newHr++;
        }
        if (newHr > 24) {
            newHr -= 24;
        }
        return MCTime(newHr, newMin);
    }
};

std::ostream & operator<<(std::ostream & os, MCTime time) {
    os << time.to_string();
    return os;
}

bool operator==(MCTime lhs, MCTime rhs) {
    return lhs.m_min == rhs.m_min && lhs.m_hour == rhs.m_hour;
}