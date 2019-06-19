#ifndef SPACE_H
#define SPACE_H

#include "celestialbody.h"
#include "hud/scale.h"
#include "hud/timehud.h"
#include "misc/vector.h"



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

        void createSolarSystem();

        Vector2D translatePoint(Vector2D point);
        sfSpace::PRECISE translateLength(sfSpace::PRECISE length);

    protected:

    private:
        Scale       m_scale;
        TimeHud     m_timehud;

        Vector2D    m_cameraposition;

        CelestialBody earth;
};

#endif // SPACE_H
