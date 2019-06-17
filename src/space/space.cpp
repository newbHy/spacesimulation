#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "celestialbody.h"
#include "space.h"



///////////////////////////////////////////////////////////////////////////////
Space::Space()
{
    //ctor
}


///////////////////////////////////////////////////////////////////////////////
Space::~Space()
{
    //dtor
}


///////////////////////////////////////////////////////////////////////////////
void Space::onUpdate(float time)
{

}


///////////////////////////////////////////////////////////////////////////////
void Space::onDraw(sf::RenderWindow* renderwindow)
{
    m_scale.draw(renderwindow);
    m_timehud.draw(renderwindow);
}


///////////////////////////////////////////////////////////////////////////////
void Space::onEvent(sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::MouseWheelScrolled :
        {
            if (event.mouseWheelScroll.delta < 0)
            {
                m_scale.setScaleFactor(m_scale.getScaleFactor() * 1.25);
            }
            else
            if (event.mouseWheelScroll.delta > 0)
            {
                m_scale.setScaleFactor(m_scale.getScaleFactor() * 0.75);
            }

            m_scale.updateScaleText();
        }
        break;
        default: break;
    }
}


///////////////////////////////////////////////////////////////////////////////
void Space::initSolarSystem()
{
    CelestialBody earth;
    earth.setMass(1.989e30);
    earth.getOrbit()->setOrbitalElements(149.60e9, 0.0167, 220, 0, 0, 0);
}
