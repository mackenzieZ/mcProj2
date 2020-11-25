//testing the main menu


#include <iostream>
#include "menu.cpp"

int main(){
    int primaryChoice, secondaryChoice, terteraryChoice;

    do{
    displayMainMenu();
    cin >> primaryChoice;

    switch(primaryChoice){
        case 1:{
        do{
            tutorMenu();
            cin >> secondaryChoice; 
            switch(secondaryChoice){
                case 1:{
                    string n_name;
                    string decision;
                    bool cleared;
                    cout << "New Name: ";
                    cin >> n_name;
                    cout << "Are they able to lead RS? 1 - yes, 0 - no ";
                    cin >> cleared;
                    cout << "Would you like to input their schedule or abilites at this time?'\n Please enter 'schedule', 'abilities', 'both' or 'neither' ";
                    cin >> decision;
                    if(decision == "schedule"){
                        shift schedule[NUM_DAYS];
                        for(int i = 0; i < NUM_DAYS; i++){
                            shift input;
                            cout << "Start :";
                            cin >> input.m_start;
                            cout << "End: ";
                            cin >> input.m_end;
                            schedule[i] = input; 
                        }
                        Tutor t1(n_name, cleared, schedule);
                    }else if(decision == "abilities"){
                        Tutor t1(n_name, cleared);
                        int j;
                        string key;
                        bool change;
                        do{
                            cout << "What class would you like to enter abilities for(all abilities defaulted to false)? ";
                            cin >> key;
                            cout << "Change abilities? yes capable - 1, not capable - 0 ";
                            cin >>  change;
                            t1.changeAbilities(key,change);
                            cout << "To end entering abilities enter 5 else press any number" << endl;
                            cin >> j;
                        }while(j !=5);
                    }else if(decision == "both"){
                        //enter both
                    }else if(decision == "neither"){
                        Tutor t1(n_name, cleared);
                    }
                    cout << "Tutor added" << endl;
                }break; //add tutor
                case 2:{

                }break; //remove tutor
                case 3:{
                    do{
                        editTutorMenu();
                        cin >> terteraryChoice;
                        if(terteraryChoice == 1){
                            //edit schedule
                        }else if(terteraryChoice == 2){
                            //edit abilities
                        }else{
                            cout << "Invalid entry" << endl;
                        }
                    }while(terteraryChoice != 0);
                }break;
            }
        }while(secondaryChoice != 0);
        }break;  
        case 2:{}break;
        case 3:{}break;
    }
    }while(primaryChoice != 0);
    

return 0;
}