#include <vector>
#include <map>

#include "action.hpp"


typedef std::vector<std::pair<int, Action>> ActionsVec;

class Replay
{
private:
    ActionsVec     m_actions;

public:
    Replay();

    void addAction(const Action& action, const int& ticks);
    ActionsVec&  getActions();
    void clear();
};