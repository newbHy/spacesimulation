#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "state.h"



class StateManager
{
public:
    StateManager();
    virtual ~StateManager();

    void changeState(State* state);

    void onDraw(sf::RenderWindow* renderwindow);

    void onUpdate(float time);

    void onEvent(sf::Event& event);

protected:

private:

    State* m_currentState;
};

#endif // STATEMANAGER_H
