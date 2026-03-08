#include "automatas.h"
#include <set>

class RabinScott final {
private:
    std::set<int> epsilonClosure(const NFA& nfa, const std::set<int>& states);
    std::set<int> epsilonClosure(const NFA& nfa, int state);
    bool containsAcceptState(const NFA& nfa, const std::set<int>& states);
    std::set<int> move_by_char(const NFA& nfa, const std::set<int>& states, char symbol);

public:
    DFA operator()(const NFA& nfa, const std::set<char>& alphabet);
};
