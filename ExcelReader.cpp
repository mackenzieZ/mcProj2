#include <OpenXLSX.hpp>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
#include "tutor.hpp"
#include "WorkDayInfo.hpp"

MCTime OPEN_TIME = MCTime("9:00");
MCTime END_TIME = MCTime("19:00");
MCTime END_TIME_FRI = MCTime("16:00");

int excel_start_rows[] {3, 25, 47, 69, 91};

using namespace OpenXLSX;

// Analyzes the scheudle Excel sheet for information usch as on which line each of the days start
std::vector<WorkDayInfo> analyzeScheduleSheet(XLWorksheet ws);
// Function to search through the Excel file and find all the different tutors, then store them in a c++ set
void findAllTutors(std::shared_ptr<std::vector<Tutor>> tutors, XLWorksheet ws);
// Helper for the findAllTutors function
void findAllTutorsInRange(std::shared_ptr<std::set<Tutor>> tutors, XLWorksheet ws, XLCellRange range);
// Go through the Excel file and find all the shifts and add them to the correct tutor
void findAllTutorShifts(std::shared_ptr<std::vector<Tutor>> tutors, XLWorksheet ws);
// Functions that returns pointer to a tutor given their name
Tutor * findTutor(std::shared_ptr<std::vector<Tutor>> tutors, std::string name);

std::shared_ptr<std::vector<Tutor>> LoadTutors(std::shared_ptr<std::vector<Tutor>> tutors, char * file_name) {
    XLDocument doc(file_name);
    XLWorksheet ws = doc.workbook().worksheet("Lab Schedule");

    std::vector<WorkDayInfo> days = analyzeScheduleSheet(ws);
    for (WorkDayInfo day : days) {
        std::cout << day.m_day << " " << day.m_openTime << " - " << day.m_closeTime << "\n";
    }

    return NULL;

    // Find all tutors from schedule file then print them out
    findAllTutors(tutors, ws);
    std::cout << "All employees in the schedule:\n";
    for (std::vector<Tutor>::iterator itr = tutors->begin(); itr != tutors->end(); itr++) 
    {
        std::cout << *itr << "\n";
    }

    // Assign the tutors their proper shifts
    findAllTutorShifts(tutors, ws);

    return tutors;
}

void findAllTutors(std::shared_ptr<std::vector<Tutor>> tutors, XLWorksheet ws) {
    auto tutor_set = std::shared_ptr<std::set<Tutor>>(new std::set<Tutor>);

    findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B3"), XLCellReference("K22")));
    findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B25"), XLCellReference("K44")));
    findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B47"), XLCellReference("K66")));
    findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B69"), XLCellReference("K88")));
    findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B91"), XLCellReference("K104")));

    for (std::set<Tutor>::iterator itr = tutor_set->begin(); itr != tutor_set->end(); itr++) 
    {
        tutors->push_back(*itr);
    }
}

void findAllTutorsInRange(std::shared_ptr<std::set<Tutor>> tutors, XLWorksheet ws, XLCellRange range) {
    for (auto & cell : range) {
        if (cell.value().valueType() == XLValueType::String) {
            tutors->insert(Tutor(cell.value().get<std::string>(), true));
        }
    }
}

void findAllTutorShifts(std::shared_ptr<std::vector<Tutor>> tutors, XLWorksheet ws) {
    for (int i = 0; i < 5; i++) {
        int shiftCount = 0;
        MCTime t = OPEN_TIME;
        while (!(t == (i < 4 ? END_TIME : END_TIME_FRI))) {
            for (int c = 1; c < 20; c++) {
                auto cell = ws.cell(XLCellReference(excel_start_rows[i] + shiftCount, c));
                if (cell.value().valueType() == XLValueType::String) {
                    std::string name = cell.value().get<std::string>();
                    Tutor * tutor = findTutor(tutors, name);
                    if (tutor) {
                        tutor->addShift(Shift(t, t.next(), Work_Day(i)));
                    }
                }
            }
            t = t.next();
            shiftCount++;
        }
    
    }
}

Tutor * findTutor(std::shared_ptr<std::vector<Tutor>> tutors, std::string name) {
    for (std::vector<Tutor>::iterator itr = tutors->begin(); itr != tutors->end(); itr++) 
    {
        if ((*itr).getName() == name) {
            return &*itr;
        }
    }
    return NULL;
}

std::vector<WorkDayInfo> analyzeScheduleSheet(XLWorksheet ws) {
    std::vector<WorkDayInfo> workdays;
    workdays.clear();
    XLCellRange range = ws.range(XLCellReference("A1"), XLCellReference("A200"));
    for (auto & cell : range) {
        if (cell.valueType() == XLValueType::Empty) continue;
        std::string str = cell.value().get<std::string>();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        Work_Day day;
        if (str == "monday") {
            day = Work_Day::MONDAY;
        }
        else if (str == "tuesday") {
            day = Work_Day::TUESDAY;
        }
        else if (str == "wednesday") {
            day = Work_Day::WEDNESDAY;
        }
        else if (str == "thursday") {
            day = Work_Day::THURSDAY;
        }
        else if (str == "friday") {
            day = Work_Day::FRIDAY;
        }
        else if (str == "saturday") {
            day = Work_Day::SATURDAY;
        }
        else if (str == "sunday") {
            day = Work_Day::SUNDAY;
        }
        else {
            continue;
        }

        int startRow = cell.cellReference().row() + 1;
        std::string startStr = ws.cell(startRow, 1).value().asString();
        MCTime start(startStr.substr(0, startStr.find("-")));
        MCTime end(0, 0);
        for (int r = startRow; ws.cell(r, 1).value().asString() != ""; r++) {
            if (ws.cell(r+1, 1).value().asString() == "") {
                std::string endStr = ws.cell(r, 1).value().asString();
                size_t pos = endStr.find("-");
                endStr.erase(0, pos + 1);
                end = MCTime(endStr);
            }
        }

        workdays.push_back(WorkDayInfo(day, start, end, startRow));
    }

    return workdays;
}
