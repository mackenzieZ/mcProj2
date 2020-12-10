#pragma once

#include <OpenXLSX.hpp>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
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


            std::string days[] {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
            int currentRow = 1;
            for (WorkDayInfo day : m_workdays) {
                save_sheet.cell(currentRow++, 1).value() = days[day.m_day];
                int dayStart = currentRow;
                for (MCTime t = day.m_openTime; !(t == day.m_closeTime); t = t.next()) {
                    save_sheet.cell(currentRow++, 1).value() = t.to_string_12() + "-" + t.next().to_string_12();
                }

                for (const Tutor & tutor : *m_tutors) {
                    currentRow = dayStart;
                    int currentCol = 2;
                    for (MCTime t = day.m_openTime; !(t == day.m_closeTime); t = t.next()) {
                        auto tutor_schedule = tutor.getSchedule();
                        if (std::find(tutor_schedule->begin(), tutor_schedule->end(), Shift(t, t.next(), day.m_day)) != tutor_schedule->end()) {
                            int originalCol = currentCol;
                            bool goNext = false;
                            while (save_sheet.cell(currentRow, currentCol).value().asString() != "" && !goNext) {
                                currentCol++;
                                for (int r = currentRow - 1; save_sheet.cell(r, originalCol).value().asString() == tutor.getName(); r--) {
                                    if (save_sheet.cell(currentRow, currentCol).value().asString() != "") {
                                        goNext = true;
                                        break;
                                    }
                                }
                            }
                            if (currentCol != originalCol) {
                                for (int r = currentRow - 1; save_sheet.cell(r, originalCol).value().asString() == tutor.getName(); r--) {
                                    save_sheet.cell(r, currentCol).value() = tutor.getName();
                                    save_sheet.cell(r, originalCol).value() = "";
                                }
                            }
                            save_sheet.cell(currentRow, currentCol).value() = tutor.getName();
                        }
                        currentRow++;
                    }
                }

                currentRow++;
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