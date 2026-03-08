#include <set>
#include <map>

struct NFA {
    int num_states;                      
    int start_state;                     
    std::set<int> accept_states;         
    std::map<std::pair<int, char>, std::set<int>> transitions;
    std::map<int, std::set<int>> epsilon_transitions;
    
    NFA(int n = 0, int start = 0) : num_states(n), start_state(start) {}
};

struct DFA {
    int num_states;                     
    int start_state;                    
    std::set<int> accept_states;             
    std::map<std::pair<int, char>, int> transitions;
    
    DFA() : num_states(0), start_state(-1) {}
};