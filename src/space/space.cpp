#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
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
// Note: this draw function currently ignores the z axis completely. Objects
//       with a high inclination (to the ecliptic) won't be drawn correctly.
//       This will be fixed once this project reaches a more mature state
void Space::onDraw(sf::RenderWindow* renderwindow)
{
    sf::CircleShape rendercircle;


    {
        Vector2D pos = translatePoint(earth.getOrbit()->getGlobalPosition());
        pos += Vector2D(renderwindow->getSize().x * 0.5, renderwindow->getSize().y * 0.5);
        auto radius = translateLength(earth.getRadius());

        rendercircle.setRadius(radius);
        rendercircle.setOrigin(radius, radius);
        rendercircle.setPosition(pos.x , pos.y);
        rendercircle.setFillColor(earth.getColor());

        renderwindow->draw(rendercircle);
    }

    m_scale.draw(renderwindow);
    m_timehud.draw(renderwindow);
}


///////////////////////////////////////////////////////////////////////////////
void Space::onEvent(sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::MouseWheelScrolled :
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
        break;
    case sf::Event::KeyPressed :
    {
        switch(event.key.code)
        {
        case sf::Keyboard::Up:
            m_cameraposition.y += m_scale.getScaleFactor() * -0.0001; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Down:
            m_cameraposition.y += m_scale.getScaleFactor() * 0.0001; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Left:
            m_cameraposition.x += m_scale.getScaleFactor() * -0.0001; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Right:
            m_cameraposition.x += m_scale.getScaleFactor() * 0.0001; // TODO change this to frame time instead of a fixed value
            break;
            default: break;
        }
    }
    break;
        default: break;
    }
}


///////////////////////////////////////////////////////////////////////////////
void Space::createSolarSystem()
{
    earth.setMass(1.989e30);
    earth.setRadius(6.371e6);
    earth.getOrbit()->setOrbitalElements(149.60e9, 0.0167, 220, 0, 0, 0);
}


///////////////////////////////////////////////////////////////////////////////
Vector2D Space::translatePoint(Vector2D point)
{
    point *= m_scale.getInvScaleFactor();

    point -= m_cameraposition;

    return point;
}


///////////////////////////////////////////////////////////////////////////////
sfSpace::PRECISE Space::translateLength(sfSpace::PRECISE length)
{
    return length * m_scale.getInvScaleFactor();
}
