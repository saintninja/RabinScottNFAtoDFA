#include "automatas.h"
#include <set>

class RabinScott {
private:
    std::set<int> epsilonClosure(const NFA& nfa, const std::set<int>& states);
    std::set<int> epsilonClosure(const NFA& nfa, int state);
    bool containsAcceptState(const NFA& nfa, const std::set<int>& states);

public:
    DFA operator()(const NFA& nfa, const std::set<char>& alphabet);
};
