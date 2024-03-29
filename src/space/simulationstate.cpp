#include "simulationstate.h"



///////////////////////////////////////////////////////////////////////////////
SimulationState::SimulationState()
{

}


///////////////////////////////////////////////////////////////////////////////
SimulationState::~SimulationState()
{

}


///////////////////////////////////////////////////////////////////////////////
SimulationState& SimulationState::getInstance()
{
    static SimulationState state;

    return state;
}


///////////////////////////////////////////////////////////////////////////////
void SimulationState::onStart()
{
    m_space.createSolarSystem();
}


///////////////////////////////////////////////////////////////////////////////
void SimulationState::onUpdate(float time)
{

}


///////////////////////////////////////////////////////////////////////////////
void SimulationState::onExit()
{

}


///////////////////////////////////////////////////////////////////////////////
void SimulationState::onDraw(sf::RenderWindow* renderwindow)
{
    m_space.onDraw(renderwindow);
}


///////////////////////////////////////////////////////////////////////////////
void SimulationState::onEvent(sf::Event& event)
{
    m_space.onEvent(event);
}
