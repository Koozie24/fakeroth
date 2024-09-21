#include <cstdlib>
#include "npc.h"
#include "character.h"
#include "quest.h"
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

std::vector<NPC> NPC::store_npc;

Main_Character handle_player_movement(Main_Character &player, char c){
    switch(c){
        case 'w':
        case 'W':
            if(player.y_pos < 150){
                player.y_pos += 5;
                player.current_direction = 'N';
            }
            clear_screen();
            break;
        case 's':
        case 'S':
            if(player.y_pos > -150){
                player.y_pos -= 5;
                player.current_direction = 'S';
            }
            clear_screen();
            break;
        case 'd':
        case 'D':
            if(player.x_pos < 150){
                player.x_pos += 5;
                player.current_direction = 'E';
            }
            clear_screen();
            break;
        case 'a':
        case 'A':
            if(player.x_pos > -150){
                player.x_pos -= 5;
                player.current_direction = 'W';
            }
            clear_screen();
            break;
    }
    return player;
}

/*This function takes a player object and two vectors as arguments. iterates through the store_npc vector, and accesses the x and y position of each npc stored to calculated the dx and dy from the player coordinate. If less than distance, the npc is added to the visible vector. 
Then runs the reverse to check for npcs that are no longer in the view distance of the player. Returns a vector that contains npc objects in view of player. */
std::vector<NPC> check_npc_in_range(Main_Character &player, std::vector<NPC> &store_npc, std::vector<NPC> &in_sight_range){
    //check for objects in line of sight of player after move
        for(int i = 0; i < NPC::store_npc.size(); i++){
            int x_distance = player.x_pos - NPC::store_npc[i].x_pos;
            int y_distance = player.y_pos - NPC::store_npc[i].y_pos;
            //if in distance add to list in line of sight
            if(abs(x_distance) <= 50 && abs(y_distance) <= 50){
                //check for object in list
                if(std::find(in_sight_range.begin(), in_sight_range.end(), NPC::store_npc[i]) == in_sight_range.end()){
                    in_sight_range.push_back(NPC::store_npc[i]);
                    std::string name_added = NPC::store_npc[i].npc_name;
                    //std::cout << name_added << " was added to in range!" << std::endl;
                }
            }
            //prints out entire list of npc's
            //std::cout << NPC::store_npc[i].npc_name <<  " xy: (" << NPC::store_npc[i].x_pos << "," << NPC::store_npc[i].y_pos << ")   ID: " << NPC::store_npc[i].npc_id << std::endl;
        }
        //std::cout << in_sight_range.size() << " is number of objects in sight range" << std::endl;

        if(in_sight_range.size() > 0){
            for(int i = 0; i < in_sight_range.size(); i++){
                int x_distance = player.x_pos - NPC::store_npc[i].x_pos;
                int y_distance = player.y_pos - NPC::store_npc[i].y_pos;
                 if(abs(x_distance) > 50 || abs(y_distance) >  50){
                    in_sight_range.erase(in_sight_range.begin() + i);
                    //std::cout << "Size of range on 168 = " << in_sight_range.size() << std::endl;
                 }
            }
        }

    return in_sight_range;
}

/*Helper function to perform euc distance calculation. Returns a double.*/
double calc_euclidean_dist(int player_x, int player_y, int npc_x, int npc_y){
    double euc_distance = sqrt(pow(player_x - npc_x, 2) + pow(player_y - npc_y, 2));

    return euc_distance;
}

void show_npc_in_range(std::vector<NPC> &in_sight_range, Main_Character &player){
    int player_x = player.x_pos;
    int player_y = player.y_pos;

    if(in_sight_range.size() > 0){
        std::cout << "You are able to see the following: " << std::endl;
        for(int i = 0; i < in_sight_range.size(); i++){
            int npc_x = in_sight_range[i].x_pos;
            int npc_y = in_sight_range[i].y_pos;
            
            double euc_distance = calc_euclidean_dist(player_x, player_y, npc_x, npc_y);

            int euc_as_int = round(euc_distance);

            std::cout << " | " << i << ": " << in_sight_range[i].npc_name << " - " << euc_as_int << "m ";
        }
        std::cout << std::endl;
    }
}

int find_friendly_in_vector(std::vector <Friendly> &store_friendly, std::string name){
    int ret_val = -1;
    for(int i = 0; i < store_friendly.size(); i++){
        if(store_friendly[i].npc_name == name){
            ret_val = i;
            break;
        }
    }
    return ret_val;
}

int main(){
    srand(time(NULL));

    int running = 1;

    clear_screen(); //clear screen and begin initialization of game objects
    initialize_quests();
    initialize_friendly_npc();
    initialize_young_wolves();
    std::vector<NPC> in_sight_range;
    Main_Character player;

    for(;;){ //start game loop

        in_sight_range = check_npc_in_range(player, NPC::store_npc, in_sight_range);
        std::cout << "Current position for " << player.player_name << " is (" << player.x_pos << "," << player.y_pos << ")." << " You are currently facing: " << player.current_direction << std::endl;
        
        show_npc_in_range(in_sight_range, player); //print npc's in range
        std::getline(std::cin >> std::ws, command); //read in command from user

        if(command.length() == 1){ //handle single character input
            char c = command[0];

            if(isdigit(c)){ //checking for integer input in command
                int int_command = int(c) - 48; //cast char back to int and subtract 0 ascii val

                if(int_command <= in_sight_range.size()){ //verify in range
                    int npc_distance = calc_euclidean_dist(player.x_pos, player.y_pos, in_sight_range[int_command].x_pos, in_sight_range[int_command].y_pos); //get euc distance
                    //seperate into helper functions at this point to handle friendly vs enemy npc's
                    int npc_disposition = in_sight_range[int_command].disposition;

                    if(npc_distance <= 16){ //check npc distance

                        //grab target
                        //int npc_loc;
                        std::string targeted_npc = in_sight_range[int_command].npc_name;
                        std::cout << "You are currently targeting: " << targeted_npc << std::endl;

                        switch(npc_disposition){//check target aggression level
                            case(0)://friendly
                                //npc_loc = find_friendly_in_vector(Friendly::store_friendly, targeted_npc);
                                //if(npc_loc >= 0){

                                //}
                                break;
                            case(1)://neutral
                                break;
                            case(2)://aggressive
                                break;
                        }

                        command.clear();
                        std::getline(std::cin >> std::ws, command); //read in new command from user
                        std::cout << command << std::endl;
                    }
                }
            }
            else if(c == 'q' || c == 'Q'){
                running = 0;
            }
            else{
                player = handle_player_movement(player, c);
            }

        }
        
        if(running == 0){
            break;
        }
    }   

    return 0;
}