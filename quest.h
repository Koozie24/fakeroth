#include <string>

struct quest_store{
    int quest_id;
    bool quest_active;
    bool quest_completed;
    int award_experience;
    std::string quest_name;
    std::string quest_dialogue;
    std::string quest_complete_dialogue;
    std::string quest_objective;
};

void initialize_quests();