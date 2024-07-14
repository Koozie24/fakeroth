#include "npc.h"
#include <vector>

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