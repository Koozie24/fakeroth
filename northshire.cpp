#include <cstdlib>
#include "npc.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <vector>
#include <cmath>

int inventory_size = 16;
std::string command = "";
int unique_id = 0;

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

std::vector<NPC> NPC::store_npc;

/*This function takes a player object and two vectors as arguments. iterates through the store_npc vector, and accesses the x and y position of each npc stored to calculated the dx and dy from the player coordinate. If less than distance, the npc is added to the visible vector. 
Then runs the reverse to check for npcs that are no longer in the view distance of the player. Returns a vector that contains npc objects in view of player. */
std::vector<NPC> check_npc_in_range(Main_Character player, std::vector<NPC> store_npc, std::vector<NPC> in_sight_range){
    //check for objects in line of sight of player after move
        for(int i = 0; i < NPC::store_npc.size(); i++){
            int x_distance = player.x_pos - NPC::store_npc[i].x_pos;
            int y_distance = player.y_pos - NPC::store_npc[i].y_pos;
            //if in distance add to list in line of sight
            if(abs(x_distance) <= 10 && abs(y_distance) <= 10){
                //check for object in list
                if(std::find(in_sight_range.begin(), in_sight_range.end(), NPC::store_npc[i]) == in_sight_range.end()){
                    in_sight_range.push_back(NPC::store_npc[i]);
                    std::string name_added = NPC::store_npc[i].npc_name;
                    //std::cout << name_added << " was added to in range!" << std::endl;
                }
            }
        }
        //std::cout << in_sight_range.size() << " is number of objects in sight range" << std::endl;

        if(in_sight_range.size() > 0){
            for(int i = 0; i < in_sight_range.size(); i++){
                int x_distance = player.x_pos - NPC::store_npc[i].x_pos;
                int y_distance = player.y_pos - NPC::store_npc[i].y_pos;
                 if(abs(x_distance) > 10 || abs(y_distance) >  10){
                    in_sight_range.erase(in_sight_range.begin() + i);
                    //std::cout << "Size of range on 168 = " << in_sight_range.size() << std::endl;
                 }
            }
        }

    return in_sight_range;
}

int main(){
    int running = 1;
    std::vector<NPC> in_sight_range;
    Main_Character player;
    NPC marshall_dughan("Marshall Dughan", "Humanoid", 5, 21, 0, 5);
    //store_npc.push_back(marshall_dughan);

    for(;;){

        in_sight_range = check_npc_in_range(player, NPC::store_npc, in_sight_range);

        //read in command from user
        std::getline(std::cin >> std::ws, command);

        //handle single character input
        if(command.length() == 1){
            char c = command[0];
            switch(c){
                case 'w':
                case 'W':
                    player.y_pos += 5;
                    player.current_direction = 'N';
                    clear_screen();
                    break;
                case 's':
                case 'S':
                    player.y_pos -= 5;
                    player.current_direction = 'S';
                    clear_screen();
                    break;
                case 'd':
                case 'D':
                    player.x_pos += 5;
                    player.current_direction = 'E';
                    break;
                case 'a':
                case 'A':
                    player.x_pos -= 5;
                    player.current_direction = 'W';
                    clear_screen();
                    break;
                case 'q':
                case 'Q':
                    running = 0;
                    break;

            }
            std::cout << "Current position for " << player.player_name << " is (" << player.x_pos << "," << player.y_pos << ")." << " You are currently facing: " << player.current_direction << std::endl;

            std::cout << "You are able to see the following creatures: " << std::endl;
            for(int i = 0; i < in_sight_range.size(); i++){
                std::cout << in_sight_range[i].npc_name << std::endl;
            }


        }
        
        if(running == 0){
            break;
        }
    }   

    return 0;
}