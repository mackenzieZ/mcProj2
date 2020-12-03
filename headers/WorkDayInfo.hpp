#pragma once

#include "MCTime.hpp"

enum Work_Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SUNDAY};

struct WorkDayInfo {
    Work_Day m_day;
    MCTime m_openTime;
    MCTime m_closeTime;
    bool m_reviewsOnly = false;
    int m_excelStartRow;

    WorkDayInfo() : m_openTime(0, 0), m_closeTime(0, 0) {};

    WorkDayInfo(Work_Day day, MCTime open, MCTime close, int row) : m_day(day), m_openTime(open), m_closeTime(close), m_excelStartRow(row) {};
};
