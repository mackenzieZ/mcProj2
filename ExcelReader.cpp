#include <OpenXLSX.hpp>
#include <iomanip>
#include <iostream>
#include <set>
#include <memory>

using namespace OpenXLSX;

// Function to search through the Excel file and find all the different tutors, then store them in a c++ set
void findAllTutors(std::shared_ptr<std::set<std::string>> tutors, XLWorksheet ws);
// Helper for the findAllTutors function
void findAllTutorsInRange(std::shared_ptr<std::set<std::string>> tutors, XLWorksheet ws, XLCellRange range);

std::shared_ptr<std::set<std::string>>  LoadTutors(char * file_name) {
    // if (argc <= 1) {
    //     std::cerr << "Error: No schedule file specified.\n";
    //     return 1;
    // }

    XLDocument doc(file_name);
    XLWorksheet ws = doc.workbook().worksheet("Lab Schedule");

    std::shared_ptr<std::set<std::string>> tutors = std::shared_ptr<std::set<std::string>>(new std::set<std::string>);

    // Find all tutors from schedule file then print them out
    findAllTutors(tutors, ws);
    std::cout << "All employees in the schedule:\n";
    for (std::set<std::string>::iterator itr = tutors->begin(); itr != tutors->end(); itr++) 
    {
        std::cout << *itr << "\n";
    }

    return tutors;
}

void findAllTutors(std::shared_ptr<std::set<std::string>> tutors, XLWorksheet ws) {
    findAllTutorsInRange(tutors, ws, ws.range(XLCellReference("B3"), XLCellReference("K22")));
    findAllTutorsInRange(tutors, ws, ws.range(XLCellReference("B25"), XLCellReference("K44")));
    findAllTutorsInRange(tutors, ws, ws.range(XLCellReference("B47"), XLCellReference("K66")));
    findAllTutorsInRange(tutors, ws, ws.range(XLCellReference("B69"), XLCellReference("K88")));
    findAllTutorsInRange(tutors, ws, ws.range(XLCellReference("B91"), XLCellReference("K104")));
}

void findAllTutorsInRange(std::shared_ptr<std::set<std::string>> tutors, XLWorksheet ws, XLCellRange range) {
    for (auto & cell : range) {
        if (cell.value().valueType() == XLValueType::String) {
            tutors->insert(cell.value().get<std::string>());
        }
    }
}

