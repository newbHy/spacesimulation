#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "states/state.h"



class StateManager
{
public:
    StateManager();
    virtual ~StateManager();

    StateManager(const StateManager& rhs) = delete;
    StateManager& operator=(const StateManager& rhs) = delete;

    void changeState(State* state);

    void onDraw(sf::RenderWindow* renderwindow);

    void onUpdate(float time);

    void onEvent(sf::Event& event);

private:
    State* m_currentState;
};

#endif // STATEMANAGER_H
