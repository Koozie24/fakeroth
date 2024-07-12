#include <iostream>
#include <string>

void clear_screen(){
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}


class Main_Character{
    public:
        std::string player_name;
        std::string player_class;
        int hit_points = 100;
        int armor = 0;
        int attack_power = 0;
        int spell_power = 0;
        int player_level = 1;
        int experience = 0;
        int x_pos = 0; //get input from user to move some number of ticks from wasd, print text to show what is within some n ticks from current xy position
        int y_pos = 0;
        char current_direction = 'N'; //can check if last move was + or - x direction for E/W and + or - y direction for N/S
        //std::map quest_log;

        Main_Character(){

            for(;;){
                int contains_digit_flag = 0;
                int max_consecutive = 0;

                std::cout << "Welcome adventurer! This is Northshire Valley. What shall we call you?" <<std::endl;
                std::cin >> player_name;
                std::cout << std::endl;
                clear_screen();
                
                //vaLidate users input checking for length and no digits or repeating characters
                char temp = '\0';
                int count_repeating = 0;

                for(char c : player_name){
                    if(isdigit(int(c))){
                        contains_digit_flag = 1;
                    }
                    
                    //check for repeating characters in given name
                    if(temp == c){
                        count_repeating++;
                    }
                    else{
                        count_repeating = 0;
                    }

                    if(count_repeating == 2){
                        max_consecutive = 1;
                    }
                    temp = c;

                }
                    
                if(player_name.length() >= 3 && player_name.length() < 13 && contains_digit_flag == 0 && max_consecutive == 0){
                    break;
                }
            }
            
            std::cout << player_name << "? Well, not what I would have stuck with that, but I suppose thats what we will call you. Now, what sort of adventurer should we train you as? You may choose: " << std::endl;

            std::cout << "Warrior" << std::endl;
            std::cout << "Hunter" << std::endl;
            std::cout << "Mage" << std::endl;
            std::cout << "Rogue" << std::endl;
            std::cout << "Paladin" << std::endl;
            std::cout << std::endl;

            for(;;){
                std::cin >> player_class;

                if(player_class == "Warrior" || player_class == "Hunter" || player_class == "Paladin" || player_class == "Mage" ||
                player_class == "Rogue"){
                    clear_screen();
                    std::cout << "Hmm, I'm not sure that I would guess you have what is takes to be a " << player_class << ", " << player_name << ", but we will see what the trainers can make of you yet. Off with you now, scum and go seek out Marshall Dughan! You will find him due north just a little ways." << std::endl;
                    break;
                }
            }
        }
};