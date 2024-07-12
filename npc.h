#include <string>
#include <vector>

extern int unique_id;

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

        NPC(std::string name, std::string type, int x, int y, int agg, int lvl){
            npc_name = name;
            npc_type = type;
            x_pos = x;
            y_pos = y;
            aggression = agg;
            level = lvl;
            hit_points = 75 + ((level - 1) * 25);
            store_npc.push_back(*this);
        }

        void assign_unique_npc_id(){
            npc_id = unique_id;
            unique_id++;
        }

        //overload comparison operator
        bool operator==(const NPC& other) const{
            return this->npc_id == other.npc_id;
        }

        std::string operator<<(const NPC& other) const{
            return this->npc_name;
        }

        static std::vector<NPC> store_npc;
};