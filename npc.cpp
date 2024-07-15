#include "npc.h"
#include <vector>
#include <random>
#include <string>

void initialize_friendly_npc(){

    std::vector<int> mcbride_quests = {2, 9, 10};
    Friendly marshall_mcbride("Marshall McBride", "Humanoid", 10, 21, 0, 5, true, mcbride_quests);

    std::vector<int> willem_quests = {0, 1, 4, 5, 8};
    Friendly deputy_willem("Deputy Willem", "Humanoid", 5, 21, 0, 5, true, willem_quests);

    std::vector<int> eagen_quests = {3};
    Friendly eagen_peltskinner("Eagen Peltskinner", "Humanoid", 25, 36, 0, 5, true, eagen_quests);

    std::vector<int> osworth_quests = {6, 7};
    Friendly milly_osworth("Milly Osworth", "Humanoid", 40, 36, 0, 5, true, osworth_quests);
}

void initialize_young_wolves(){
    std::string npc_type = "Beast";
    int agg = 1;
    
    for(int i=0; i < 18; i++){
        std::string wolf_name = "Young Wolf ";
        wolf_name = wolf_name + std::to_string(i);
        int wolf_level = rand() % 3 + 1;
        int x_spawn = rand() % 150 + -75;
        int y_spawn = rand() % 150 + -75;

        new Neutral (wolf_name, npc_type, x_spawn, y_spawn, agg, wolf_level);
    }
}