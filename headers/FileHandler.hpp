#pragma once

#include <OpenXLSX.hpp>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>
#include "tutor.hpp"
#include "WorkDayInfo.hpp"

using namespace OpenXLSX;

class FileHandler {
    public:
        FileHandler(std::shared_ptr<std::vector<Tutor>> tutors, std::string filename) : m_tutors(tutors), m_filename(filename) {
            std::shared_ptr<XLDocument> doc(new XLDocument(filename));
            m_doc = doc;
            m_ws = m_doc->workbook().worksheet("Lab Schedule");
        }

        // Function to search through the Excel file and find all the different tutors, then store them in a c++ set
        void findAllTutors() {
            analyzeScheduleSheet();
            auto tutor_set = std::shared_ptr<std::set<Tutor>>(new std::set<Tutor>);

            for (auto day : m_workdays) {
                findAllTutorsInRange(tutor_set, m_ws.range(XLCellReference(day.m_excelStartRow, 2), XLCellReference(day.m_excelStartRow + day.GetShiftCount(), 11)));
            }
            
            // findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B3"), XLCellReference("K22")));
            // findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B25"), XLCellReference("K44")));
            // findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B47"), XLCellReference("K66")));
            // findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B69"), XLCellReference("K88")));
            // findAllTutorsInRange(tutor_set, ws, ws.range(XLCellReference("B91"), XLCellReference("K104")));

            for (std::set<Tutor>::iterator itr = tutor_set->begin(); itr != tutor_set->end(); itr++) 
            {
                m_tutors->push_back(*itr);
            }

            findAllTutorShifts();
        }

        void saveScheduleFile() {
            XLDocument doc;
            doc.create("save_schedule.xlsx");
            auto save_sheet = doc.workbook().worksheet("Sheet1");
            save_sheet.setName("Lab Schedule");


            std::string days[] {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            int dayStartRows[7] = {0};
            int currentRow = 1;
            for (WorkDayInfo day : m_workdays) {
                save_sheet.cell(currentRow++, 1).value() = days[day.m_day];
                int dayStart = currentRow;
                dayStartRows[day.m_day] = dayStart;
                for (MCTime t = day.m_openTime; !(t == day.m_closeTime); t = t.next()) {
                    save_sheet.cell(currentRow++, 1).value() = t.to_string_12() + "-" + t.next().to_string_12();
                }
                currentRow++;
            }

            std::vector<std::tuple<int, int, int, Tutor>> occupiedCells;

            for (const Tutor & tutor : *m_tutors) {
                std::vector<std::tuple<MCTime, MCTime, Work_Day>> shiftDurations;
                Shift startShift;
                MCTime shiftEnd(0, 0);
                for (int i = 0; i < tutor.getSchedule()->size(); i++) {
                    if (i != 0 && (*tutor.getSchedule())[i].m_start == shiftEnd && (*tutor.getSchedule())[i].m_day == startShift.m_day) {
                        shiftEnd = (*tutor.getSchedule())[i].m_end;
                    }
                    else {
                        if (i != 0) {
                            shiftDurations.push_back(std::tuple<MCTime, MCTime, Work_Day>(startShift.m_start, shiftEnd, startShift.m_day));
                        }
                        startShift = (*tutor.getSchedule())[i];
                        shiftEnd = startShift.m_end;
                    }
                }
                shiftDurations.push_back(std::tuple<MCTime, MCTime, Work_Day>(startShift.m_start, shiftEnd, startShift.m_day));

                for (auto tuple : shiftDurations) {
                    int startRow = dayStartRows[std::get<2>(tuple)];
                    int currentRow = startRow;
                    MCTime shiftStartTime = std::get<0>(tuple);
                    MCTime shiftEndTime = std::get<1>(tuple);
                    WorkDayInfo dayInfo;
                    for (WorkDayInfo d : m_workdays) {
                        if (d.m_day == std::get<2>(tuple)) {
                            dayInfo = d;
                        }
                    }
                    for (MCTime t = dayInfo.m_openTime; !(t == dayInfo.m_closeTime) && !(t == shiftStartTime); t = t.next()) {
                        currentRow++;
                    }
                    int shiftStartRow = currentRow;
                    bool spotFound = false;
                    int col = 1;
                    while (!spotFound) {
                        currentRow = shiftStartRow;
                        col++;
                        bool occupied = false;
                        for (MCTime t = shiftStartTime; !(t == shiftEndTime); t = t.next()) {
                            if (save_sheet.cell(currentRow++, col).value().asString() != "") {
                                occupied = true;
                                break;
                            }
                        }
                        spotFound = !occupied;
                    }
                    
                    currentRow = shiftStartRow;
                    for (MCTime t = shiftStartTime; !(t == shiftEndTime); t = t.next()) {
                        save_sheet.cell(currentRow++, col).value() = tutor.getName();
                    }
                }
            }

            doc.save();
        }
        
        // Functions that returns pointer to a tutor given their name
        Tutor * findTutor(std::string name) {
            for (std::vector<Tutor>::iterator itr = m_tutors->begin(); itr != m_tutors->end(); itr++) {
                if ((*itr).getName() == name) {
                    return &*itr;
                }
            }
            return NULL;
        }

    private:
        // Analyzes the scheudle Excel sheet for information usch as on which line each of the days start
        void analyzeScheduleSheet() {
            m_workdays.clear();
            XLCellRange range = m_ws.range(XLCellReference("A1"), XLCellReference("A200"));
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
                std::string startStr = m_ws.cell(startRow, 1).value().asString();
                MCTime start(startStr.substr(0, startStr.find("-")));
                MCTime end(0, 0);
                for (int r = startRow; m_ws.cell(r, 1).value().asString() != ""; r++) {
                    if (m_ws.cell(r+1, 1).value().asString() == "") {
                        std::string endStr = m_ws.cell(r, 1).value().asString();
                        size_t pos = endStr.find("-");
                        endStr.erase(0, pos + 1);
                        end = MCTime(endStr).pm();
                    }
                }

                m_workdays.push_back(WorkDayInfo(day, start, end, startRow));
            }
        }

        // Helper for the findAllTutors function
        void findAllTutorsInRange(std::shared_ptr<std::set<Tutor>> tutors, XLCellRange range) {
            for (auto & cell : range) {
                if (cell.value().valueType() == XLValueType::String) {
                    tutors->insert(Tutor(cell.value().get<std::string>(), true));
                }
            }
        }

        // Go through the Excel file and find all the shifts and add them to the correct tutor
        void findAllTutorShifts() {
            for (int i = 0; i < 5; i++) {
                int shiftCount = 0;
                MCTime t = m_workdays[i].m_openTime;
                while (!(t == m_workdays[i].m_closeTime)) {
                    for (int c = 1; c < 20; c++) {
                        auto cell = m_ws.cell(XLCellReference(m_workdays[i].m_excelStartRow + shiftCount, c));
                        if (cell.value().valueType() == XLValueType::String) {
                            std::string name = cell.value().get<std::string>();
                            Tutor * tutor = findTutor(name);
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

        std::string m_filename;
        XLWorksheet m_ws;
        std::shared_ptr<XLDocument> m_doc;
        std::shared_ptr<std::vector<Tutor>> m_tutors;
        std::vector<WorkDayInfo> m_workdays;
};