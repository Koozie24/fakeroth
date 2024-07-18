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

/*This function takes a player object and two vectors as arguments. iterates through the store_npc vector, and accesses the x and y position of each npc stored to calculated the dx and dy from the player coordinate. If less than distance, the npc is added to the visible vector. 
Then runs the reverse to check for npcs that are no longer in the view distance of the player. Returns a vector that contains npc objects in view of player. */
std::vector<NPC> check_npc_in_range(Main_Character player, std::vector<NPC> store_npc, std::vector<NPC> in_sight_range){
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

void show_npc_in_range(std::vector<NPC> in_sight){
    if(in_sight.size() > 0){
            std::cout << "You are able to see the following: " << std::endl;
            for(int i = 0; i < in_sight.size(); i++){

                std::cout << " | " << i << ": " << in_sight[i].npc_name;
            }
            std::cout << std::endl;
        }
}

/*Helper function to perform euc distance calculation. Returns a double.*/
double calc_euclidean_dist(int player_x, int player_y, int npc_x, int npc_y){
    double euc_distance = sqrt(pow(player_x - npc_x, 2) + pow(player_y - npc_y, 2));

    return euc_distance;
}

/*Function takes two arguments, a vector of NPCs and a main character object. Accesses xy values for each npc and player. Calculates euclidean distance and prints to terminal*/
void update_euclidean_distance_from_npc_in_sight(std::vector<NPC> in_sight_range, Main_Character player){

    int player_x = player.x_pos;
    int player_y = player.y_pos;

    for(int i = 0; i < in_sight_range.size(); i++){
        int npc_x = in_sight_range[i].x_pos;
        int npc_y = in_sight_range[i].y_pos;

        double euc_distance = calc_euclidean_dist(player_x, player_y, npc_x, npc_y);

        int euc_as_int = round(euc_distance);
        //std::cout << "euclidean distance is: " << euc_as_int << std::endl;

    }
}

int main(){
    srand(time(NULL));

    int running = 1;

    clear_screen();
    initialize_quests();
    initialize_friendly_npc();
    initialize_young_wolves();
    std::vector<NPC> in_sight_range;
    Main_Character player;

    for(;;){

        in_sight_range = check_npc_in_range(player, NPC::store_npc, in_sight_range);

        if(in_sight_range.size() > 0){
            update_euclidean_distance_from_npc_in_sight(in_sight_range, player);
        }

        std::cout << "Current position for " << player.player_name << " is (" << player.x_pos << "," << player.y_pos << ")." << " You are currently facing: " << player.current_direction << std::endl;
        
        //print npc's in range
        show_npc_in_range(in_sight_range);

        //read in command from user
        std::getline(std::cin >> std::ws, command);

        //handle single character input
        if(command.length() == 1){
            char c = command[0];
            if(isdigit(c)){ //checking for integer input in command
                int int_command = int(c);
                if(int_command <= in_sight_range.size()){ //verify in range
                    int npc_distance = calc_euclidean_dist(player.x_pos, player.y_pos, in_sight_range[int_command].x_pos, in_sight_range[int_command].y_pos); //get euc distance
                    //seperate into helper functions at this point to handle friendly vs enemy npc's
                    int npc_disposition = in_sight_range[int_command].disposition;
                    if(npc_distance <= 6){ //check distance
                        command.clear();
                        //read in new command from user
                        std::getline(std::cin >> std::ws, command);
                        std::cout << command << std::endl;
                    }
                }
            }
            else{
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
                    case 'q':
                    case 'Q':
                        running = 0;
                        break;
                }
            }

        }

        /*
        for(int i=0; i < NPC::store_npc.size(); i++){
            std::cout << NPC::store_npc[i].npc_name << " at position: " << NPC::store_npc[i].x_pos << "," << NPC::store_npc[i].y_pos << std::endl;
        }*/
        
        if(running == 0){
            break;
        }
    }   

    return 0;
}