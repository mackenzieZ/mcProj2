//testing the main menu

#include "menu.cpp"
#include "ExcelReader.cpp"


int main(int argc, char ** argv) {
    int primaryChoice, secondaryChoice, terteraryChoice;
    std::shared_ptr<std::vector<Tutor>> tutorList(new std::vector<Tutor>);
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
                        case 1://add staff
                        {
                            std::string n_name;
                            int decision, type;
                            bool cleared;
                            std::cout << "New Name: ";
                            std::cin >> n_name;
                            if(findTutor(tutorList, n_name) != NULL){
                                std::cout << "Staff Name Already taken - try again" << std::endl;
                                break;
                            }
                            std::cout << "Are they a tutor or FD staff? 1 - Tutor, 0 - FD ";
                            std::cin >> type;
                            std::cout << "Are they able to lead RS? 1 - yes, 0 - no ";
                            std::cin >> cleared;
                            std::cout << "Would you like to input their schedule or abilites at this time?'\n Please enter 1- schedule, 2 - abilities, 3 - both, 0 - neither: ";
                            std::cin >> decision;
                            switch(decision){
                                //need a way to add these new tutors to the tutorlist
                                case 1://manual entering schedule
                                {
                                std::shared_ptr<std::vector<Shift>> initial_schedule(new std::vector<Shift>);
                                scheduleMenuOption(initial_schedule);
                                Tutor t1(n_name, cleared, initial_schedule);
                                tutorList->push_back(t1);
                                }break;
                                case 2://manual entering abilities
                                {
                                if(type == 0){
                                    std::cout << "The Staff member you added is a FD and does not have tutor abilities" << std::endl;
                                    Tutor manualTutorEntry(n_name, cleared, Employee_Type::FD);
                                    tutorList->push_back(manualTutorEntry);
                                    break;
                                }
                                Tutor manualTutorEntry(n_name, cleared);
                                abilitiesMenuOption(manualTutorEntry);
                                tutorList->push_back(manualTutorEntry);

                                }break;
                                case 3://entering both manually
                                {
                                std::shared_ptr<std::vector<Shift>> initial_schedule(new std::vector<Shift>);
                                scheduleMenuOption(initial_schedule);
                                if(type == 0){
                                    std::cout << "The Staff member you added is a FD and does not have tutor abilities" << std::endl;
                                    Tutor t1(n_name, cleared, initial_schedule, Employee_Type::FD);
                                    tutorList->push_back(t1);
                                    break;
                                }
                                Tutor t1(n_name, cleared, initial_schedule);
                                abilitiesMenuOption(t1);
                                tutorList->push_back(t1);
                                }break;
                                case 0://entering neither
                                {
                                if(type == 0){
                                    Tutor t1(n_name, cleared, Employee_Type::FD);
                                    tutorList->push_back(t1);
                                    break;
                                }
                                Tutor t1(n_name, cleared);
                                tutorList->push_back(t1);
                                }break;
                            }

                            std::cout << "Staff member added" << std::endl;
                        } break;
                        case 2://remove tutor
                        {
                            std::string tutorToRemove;
                            int position;
                            if(tutorList->empty()){
                                std::cout << "There are no tutors to remove" << std::endl;
                                break;
                            }
                            std::cout << "Enter the Tutor's Name you wish to remove:" << std::endl;
                            std::cin >> tutorToRemove;
                            //find location of said tutor in list and return position * 1 = pos rn**
                            position = findPosition(tutorList, tutorToRemove);
                            if(position >= 0){
                                tutorList->erase(tutorList->begin()+position);
                                std::cout << position << std::endl;
                                std::cout << "Staff member removed" << std::endl;
                            }else{
                                std::cout << "Staff member not found in list; unable to remove" << std::endl;
                            }


                        } break;
                        case 3:{
                            //checking to see if there are tutors in the list to edit
                            //Does not work
                            if(tutorList->empty()){
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
                                if(findTutor(tutorList, tutorToEdit) == NULL){
                                    std::cout << "This tutor does not exist on the list" << std::endl;
                                }

                                if(terteraryChoice == 1){
                                    //edit schedule
                                    findTutor(tutorList, tutorToEdit)->displaySchedule();
                                    
                                }else if(terteraryChoice == 2){
                                    //edit abilities
                                    findTutor(tutorList, tutorToEdit)->printAbilities();
                                    
                                }else{
                                    std::cout << "Invalid entry" << std::endl;
                                }
                            }while(terteraryChoice != 0);
                        } break;
                        case 4: {
                            tutorList = LoadTutors(tutorList, "schedule.xlsx");
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

