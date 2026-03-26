#include "RabinScottConverter.h"
#include <queue>
#include <map>

std::set<int> RabinScott::epsilonClosure(const NFA& nfa, const std::set<int>& states) {
    std::set<int> closure = states;
    std::queue<int> q;

    for (int state : states) {
        q.push(state);
    }
    
    while (!q.empty()) {
        int current = q.front(); q.pop();
        
        if (nfa.epsilon_transitions.count(current)) {
            for (int next : nfa.epsilon_transitions.at(current)) {
                if (closure.find(next) == closure.end()) {
                    closure.insert(next);
                    q.push(next);
                }
            }
        }
    }
    
    return closure;
}

std::set<int> RabinScott::epsilonClosure(const NFA& nfa, int state) {
    return epsilonClosure(nfa, {state});
}

std::set<int> RabinScott::move_by_char(const NFA& nfa, const std::set<int>& states, char symbol) {
    std::set<int> result;
    
    for (int state : states) {
        std::pair<int, char> key = {state, symbol};
        if (nfa.transitions.count(key)) {
            for (int next : nfa.transitions.at(key)) {
                result.insert(next);
            }
        }
    }
    
    return result;
}

bool RabinScott::containsAcceptState(const NFA& nfa, const std::set<int>& states) {
    for (int state : states) {
        if (nfa.accept_states.count(state)) {
            return true;
        }
    }
    return false;
}

DFA RabinScott::operator()(const NFA& nfa, const std::set<char>& alphabet) {
    DFA dfa;

    std::map<std::set<int>, int> state_mapping;
    std::queue<std::set<int>> unprocessed;
    
    std::set<int> start_closure = epsilonClosure(nfa, nfa.start_states);
    state_mapping[start_closure] = 1;
    dfa.start_state = 1;
    unprocessed.push(start_closure);
    
    if (containsAcceptState(nfa, start_closure)) {
        dfa.accept_states.insert(1);
    }
    
    int dfa_state_counter = 2;
    
    while (!unprocessed.empty()) {
        std::set<int> current_NFA_states = unprocessed.front();
        unprocessed.pop();
        
        int current_DFA_state = state_mapping[current_NFA_states];
        
        for (char symbol : alphabet) {
            std::set<int> moved = move_by_char(nfa, current_NFA_states, symbol);
            
            if (moved.empty()) {
                continue; 
            }
            
            std::set<int> next_NFA_states = epsilonClosure(nfa, moved);
            
            if (state_mapping.find(next_NFA_states) == state_mapping.end()) {
                state_mapping[next_NFA_states] = dfa_state_counter;
                
                if (containsAcceptState(nfa, next_NFA_states)) {
                    dfa.accept_states.insert(dfa_state_counter);
                }
                
                unprocessed.push(next_NFA_states);
                dfa_state_counter++;
            }
            
            int nextDFAState = state_mapping[next_NFA_states];
            dfa.transitions[{current_DFA_state, symbol}] = nextDFAState;
        }
    }
    
    dfa.num_states = dfa_state_counter - 1;
    return dfa;
}
