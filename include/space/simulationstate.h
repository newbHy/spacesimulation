#ifndef SIMULATIONSTATE_H
#define SIMULATIONSTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "space/space.h"
#include "states/state.h"



class SimulationState : public State
{
    public:

        static SimulationState& getInstance();

        virtual ~SimulationState();

        virtual void onStart() override;

        virtual void onExit() override;

        virtual void onUpdate(float time) override;

        virtual void onDraw(sf::RenderWindow* renderwindow) override;

        virtual void onEvent(sf::Event& event) override;

    private:

        SimulationState();

        Space m_space;
};

#endif // SIMULATIONSTATE_H
