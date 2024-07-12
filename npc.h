#include <string>
#include <vector>

extern int unique_id;

//base class for all non player characters
class NPC{
    public:
        std::string npc_name = "";
        std::string npc_type = "";
        //0 if friently 1 if neutral 2 if enemy
        int aggression;
        int level;
        int hit_points;
        int x_pos;
        int y_pos;
        int npc_id;

        void assign_unique_npc_id(){
            npc_id = unique_id;
            unique_id++;
        }

        //overload comparison operator
        bool operator==(const NPC& other) const{
            return this->npc_id == other.npc_id;
        }

        //overload output operator for NPC object
        std::string operator<<(const NPC& other) const{
            return this->npc_name;
        }

        static std::vector<NPC> store_npc;
};

class Enemy: public NPC{
    public:
        Enemy(std::string name, std::string type, int x, int y, int agg, int lvl){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            aggression = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            store_npc.push_back(*this);
        }
};

class Friendly : public NPC{
    public:
        bool quest_giver;
        Friendly(std::string name, std::string type, int x, int y, int agg, int lvl, bool has_quest, int quest_id = 0){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            aggression = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            quest_giver = has_quest;

            if(quest_giver == true){
                
            }
            store_npc.push_back(*this);
        }

        std::string give_quest_to_player(){
            std::string quest_text_string;
        }
};

class Neutral: public NPC{
    public:
        Neutral(std::string name, std::string type, int x, int y, int agg, int lvl){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            aggression = agg;
            level = lvl;
            hit_points = 50 + ((level - 1) * 25);
            store_npc.push_back(*this);
        }
};
