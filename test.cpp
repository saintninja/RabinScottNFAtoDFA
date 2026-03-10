#include "RabinScottConverter.h"

int main() {
    NFA nfa;
    nfa.num_states = 3;
    nfa.start_states = {1};
    nfa.accept_states = {3};
    nfa.epsilon_transitions = {{1, {2}}};
    nfa.transitions = {{{2, 'a'}, {1}}
                     , {{2, 'b'}, {3}}
                     , {{3, 'a'}, {3}}
                     , {{3, 'b'}, {3}}};
    std::cout << nfa;
    RabinScott converter;
    DFA dfa = converter(nfa, {'a', 'b'});
    std::cout << dfa;
    return 0;
}