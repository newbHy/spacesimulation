#include "statemanager.h"



///////////////////////////////////////////////////////////////////////////////
StateManager::StateManager() : m_currentState(nullptr)
{
    //ctor
}


///////////////////////////////////////////////////////////////////////////////
StateManager::~StateManager()
{
    //dtor
}


///////////////////////////////////////////////////////////////////////////////
void StateManager::changeState(State* state)
{
    if (state == nullptr)
        return;

    if (m_currentState)
        m_currentState->onExit();

    m_currentState = state;

    m_currentState->onStart();
}


///////////////////////////////////////////////////////////////////////////////
void StateManager::onEvent(sf::Event& event)
{
    if (m_currentState)
        m_currentState->onEvent(event);
}


///////////////////////////////////////////////////////////////////////////////
void StateManager::onDraw(sf::RenderWindow* renderwindow)
{
    if (m_currentState)
        m_currentState->onDraw(renderwindow);
}


///////////////////////////////////////////////////////////////////////////////
void StateManager::onUpdate(float time)
{
    if (m_currentState)
        m_currentState->onUpdate(time);
}
