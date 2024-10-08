#include <string>
#include <vector>

//base class for all non player characters
class NPC{
    public:
        std::string npc_name = "";
        std::string npc_type = "";
        //0 if friently 1 if neutral 2 if enemy
        int disposition;
        int level;
        int hit_points;
        int x_pos;
        int y_pos;
        int npc_id;
        int unique_id;

        //overload comparison operator
        bool operator==(const NPC& other) const{
            return this->unique_id == other.unique_id;
        }

        //overload output operator for NPC object
        std::string operator<<(const NPC& other) const{
            return this->npc_name;
        }

        static std::vector<NPC> store_npc;
};

class Enemy: public NPC{
    public:
        Enemy(std::string name, std::string type, int x, int y, int agg, int lvl, int npc_id){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            disposition = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            unique_id = npc_id;
            store_npc.push_back(*this);
        }
};

class Friendly : public NPC{
    public:
        bool quest_giver;
        std::vector<int> quests_offered;
        static std::vector<Friendly> store_friendly;
        Friendly(std::string name, std::string type, int x, int y, int agg, int lvl, bool has_quest, std::vector<int> quest_ids, int npc_id){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            disposition = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            quest_giver = has_quest;
            unique_id = npc_id;

            if(quest_giver == true){
                quests_offered = quest_ids;
            }
            store_npc.push_back(*this);
           // store_friendly.push_back(*this);
        }

        /*
        std::string give_quest_to_player(){
            std::string quest_text_string;
        }
        */
};

class Neutral: public NPC{
    public:
        Neutral(std::string name, std::string type, int x, int y, int agg, int lvl, int npc_id){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            disposition = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            unique_id = npc_id;
            store_npc.push_back(*this);
        }
};

void initialize_friendly_npc();
void initialize_young_wolves(); //neutral
void initialize_kobold_vermin(); //neutral
void initialize_kobold_workers(); //enemy
void initialize_kobold_laborers(); //enemy
void initialize_defias_thieves(); //enemy
void initialize_garrick_padfoot(); //enemy - elite?
