#pragma once

#include <OpenXLSX.hpp>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>
#include <filesystem>
#include "tutor.hpp"
#include "WorkDayInfo.hpp"
#include "FileHandler.hpp"

using namespace OpenXLSX;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

struct TutorPreferences {
    std::string name;
    XLWorksheet preferenceSheet;
    std::vector<Shift> availableShifts;

    TutorPreferences(std::string _name) : name(_name) {};
};

class ScheduleGenerator {
    public:
        ScheduleGenerator(std::string path, FileHandler & fh) : m_file_handler(fh) {
            m_folder_path = path;
        }

        void GenerateSchedule(std::shared_ptr<std::vector<Tutor>> tutorList) {
            for (const auto& dirEntry : recursive_directory_iterator(m_folder_path)) {
                if (dirEntry.path().filename().string()[0] == '~' || dirEntry.path().filename().string()[0] == '.')  continue;
                std::cout << dirEntry.path().string() << std::endl;
                TutorPreferences tp = TutorPreferences(dirEntry.path().filename().stem().string());
                tp.preferenceSheet = XLDocument(dirEntry.path().string()).workbook().worksheet("Sheet1");
                m_preferences.push_back(tp);
            }

            for (TutorPreferences tp : m_preferences) {
                for (WorkDayInfo day : m_file_handler.getWorkDaysInfo()) {
                    int row = day.m_excelStartRow;
                    for (MCTime t = day.m_openTime; !(t == day.m_closeTime); t = t.next()) {
                        if (tp.preferenceSheet.cell(row, 2).value().asString() == "X") {
                            tp.availableShifts.push_back(Shift(t, t.next(), day.m_day));
                        }
                    }
                }

                for (Shift s : tp.availableShifts) {
                    std::cout << tp.name << " " << s.to_string() << "\n";
                }
            }

        }

    private:
        std::string m_folder_path;
        std::vector<TutorPreferences> m_preferences;
        FileHandler m_file_handler;
};