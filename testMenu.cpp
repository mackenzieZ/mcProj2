//testing the main menu

#include "menu.cpp"
#include "ExcelReader.cpp"


int main(int argc, char ** argv) {
    int primaryChoice, secondaryChoice, terteraryChoice;
    std::shared_ptr<std::vector<Tutor>> tutorList;
    do {
        displayMainMenu();
        std::cin >> primaryChoice;

        switch (primaryChoice) {
            case 1://Tutor Information Menu 
            {
                do {
                    tutorMenu();
                    std::cin >> secondaryChoice; 
                    switch(secondaryChoice){
                        case 1://add tutor
                        {
                            std::string n_name;
                            std::string decision;
                            bool cleared;
                            std::cout << "New Name: ";
                            std::cin >> n_name;
                            std::cout << "Are they able to lead RS? 1 - yes, 0 - no ";
                            std::cin >> cleared;
                            std::cout << "Would you like to input their schedule or abilites at this time?'\n Please enter 'schedule', 'abilities', 'both' or 'neither' ";
                            std::cin >> decision;
                            if (decision == "schedule") {
                                Shift * initial_schedule = scheduleMenuOption();
                                Tutor t1(n_name, cleared, initial_schedule);
                            } else if(decision == "abilities") {
                                Tutor t1(n_name, cleared);
                                abilitiesMenuOption(t1);
                            } else if(decision == "both") {
                                Shift * initial_schedule = scheduleMenuOption();
                                Tutor t1(n_name, cleared, initial_schedule);
                                abilitiesMenuOption(t1);
                            } else if(decision == "neither") {
                                Tutor t1(n_name, cleared);
                            }
                            std::cout << "Tutor added" << std::endl;
                        } break;
                        case 2://remove tutor
                        {
                        } break;
                        case 3:{
                            //checking to see if there are tutors in the list to edit
                            if(tutorList == NULL){
                                std::cout << "There are no tutors to edit, add tutor to edit" << std::endl;
                                break;
                            }
                            //else display menu to edit tutor
                            do{
                                editTutorMenu();
                                std::string tutorToEdit;
                                std::cin >> terteraryChoice;
                                std::cout << "Enter the Tutor's Name you wish to edit" << std::endl;
                                std::cin >> tutorToEdit;
                                if(terteraryChoice == 1){
                                    //edit schedule
                                    //tutorList = global object for 
                                    findTutor(tutorList, tutorToEdit)->displaySchedule();
                                    
                                }else if(terteraryChoice == 2){
                                    //edit abilities
                                }else{
                                    std::cout << "Invalid entry" << std::endl;
                                }
                            }while(terteraryChoice != 0);
                        } break;
                        case 4: {
                            LoadTutors("schedule.xlsx");
                        } break;
                    }
                } while(secondaryChoice != 0);
            } break;  
            case 2://Course Information
            {}break;
            case 3://Generate Review
            {}break;
        }
    } while(primaryChoice != 0);
    

    return 0;
}

