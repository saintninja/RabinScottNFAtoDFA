#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <set>
#include <map>
#include <iostream>

struct NFA {
    int num_states;                      
    std::set<int> start_states;                     
    std::set<int> accept_states;         
    std::map<std::pair<int, char>, std::set<int>> transitions;
    std::map<int, std::set<int>> epsilon_transitions;
    
    NFA(int n = 0, std::set<int> start = {0}) : num_states(n), start_states(start) {}
};

struct DFA {
    int num_states;                     
    int start_state;                    
    std::set<int> accept_states;             
    std::map<std::pair<int, char>, int> transitions;
    
    DFA() : num_states(0), start_state(-1) {}
};

inline std::ostream& operator<<(std::ostream &os, const NFA& nfa) {
    os << "States: 1-" << (nfa.num_states) << std::endl;
    os << "Start state: { "; 
    for (int s : nfa.start_states) os << s << " ";
    os << "}" << std::endl;
    os << "Accept states: { ";
    for (int s : nfa.accept_states) os << s << " ";
    os << "}" << std::endl;
    
    os << "Transitions:" << std::endl;
    for (const auto& trans : nfa.transitions) {
        os << "  " << trans.first.first << " by " << trans.first.second 
             << " --> { ";
        for (int s : trans.second) os << s << " ";
        os << "}" << std::endl;
    }
    
    if (!nfa.epsilon_transitions.empty()) {
        os << "eps-transitions:" << std::endl;
        for (const auto& trans : nfa.epsilon_transitions) {
            os << "  " << trans.first << " --eps--> { ";
            for (int s : trans.second) os << s << " ";
            os << "}" << std::endl;
        }
    }
    os << std::endl;
    return os;
}

inline std::ostream& operator<<(std::ostream &os, const DFA& dfa) {
    os << "States: 1-" << (dfa.num_states) << std::endl;
    os << "Start state: " << dfa.start_state << std::endl;
    os << "Accept states: { ";
    for (int s : dfa.accept_states) os << s << " ";
    os << "}" << std::endl;
    
    os << "Transitions:" << std::endl;
    for (const auto& trans : dfa.transitions) {
        os << "  " << trans.first.first << " by " << trans.first.second 
             << " --> " << trans.second << std::endl;
    }
   
    os << std::endl;
    return os;
}

#endif