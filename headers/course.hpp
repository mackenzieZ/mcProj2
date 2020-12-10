#include <string>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>

enum Exam_Month {JAN,FEB,MARCH,APRIL,MAY,JUNE,JULY,AUG,SEPT,OCT,NOV,DEC};

struct Exam{
    int m_number;
    Exam_Month m_month;
    

};

class Course{
    public:

    Course() : m_prof(0), m_name(0), m_section(0){}


    
    
    //Setters
    void setProf(std::string prof){ m_prof = prof; }
    void setName(std::string name){ m_name = name; }
    void setSection(int section){ m_section = section; }


    //Getters
    std::string getProf() const { return m_prof; }
    std::string getName() const { return m_name; }
    int getSection() const {return m_section; }

    // Operators needed for compatibilty sake
    friend bool operator==(const Course & lhs, const Course & rhs);

    friend bool operator<(const Course & lhs, const Course & rhs);

    friend bool operator>(const Course & lhs, const Course & rhs);

    friend std::ostream & operator<<(std::ostream & os, const Course & course);


    private:
    std::string m_prof;
    std::string m_name;
    int m_section;
    std::shared_ptr<std::vector<Exam>> m_examDates;


};

std::ostream & operator<<(std::ostream & os, const Course & course) {
    os << course.m_name << " " << course.m_prof << " " << course.m_section;
    return os;
}

bool operator==(const Course & lhs, const Course & rhs) {
    return (lhs.m_name == rhs.m_name) && (lhs.m_section == rhs.m_section);
}

bool operator<(const Course & lhs, const Course & rhs) {
    return lhs.m_name < rhs.m_name;
}

bool operator>(const Course & lhs, const Course & rhs) {
    return lhs.m_name > rhs.m_name;
}