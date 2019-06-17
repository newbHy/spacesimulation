#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>



class State
{
    public:
        virtual ~State() {}

        virtual void onStart()=0;

        virtual void onUpdate(float time)=0;

        virtual void onExit()=0;

        virtual void onDraw(sf::RenderWindow* renderwindow)=0;

        virtual void onEvent(sf::Event& event)=0;
};

#endif // STATEM_H
