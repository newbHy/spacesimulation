#ifndef SPACE_H
#define SPACE_H

#include "hud/scale.h"
#include "hud/timehud.h"



namespace sf
{
class RenderWindow;
class Event;
}

class Space
{
    public:
        Space();
        virtual ~Space();

        void onUpdate(float time);

        void onDraw(sf::RenderWindow* renderwindow);

        void onEvent(sf::Event& event);

        void initSolarSystem();

    protected:

    private:

        Scale   m_scale;
        TimeHud m_timehud;
};

#endif // SPACE_H
