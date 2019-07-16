#include "space/space.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "assets/resourcemanager.h"
#include "si/metrics.h"
#include "space/celestialbody.h"
#include "space/orbitalelements.h"
#include "space/timefunctions.h"



////////////////////////////////////////////////////////////////////////////////
Space::Space()
  : m_timescale(1.0),
    m_followme(nullptr),
    m_selectme(nullptr),
    m_isfollowing(false)
{
    // ...
}


////////////////////////////////////////////////////////////////////////////////
Space::~Space()
{
    clearBodies();
}


////////////////////////////////////////////////////////////////////////////////
void Space::onUpdate(float time)
{
    m_timehud.advanceTime(time * m_timescale);

    for(auto it = m_bodies.begin();it != m_bodies.end();it++)
    {
        (*it)->getOrbit()->update(time * m_timescale);
    }
}


////////////////////////////////////////////////////////////////////////////////
void Space::onDraw(sf::RenderWindow* renderwindow)
{
    if (isFollowing())
        lookAt(m_followme);

    for(auto it = m_bodies.begin();it != m_bodies.end();it++)
    {
        drawCircularObject(*it, renderwindow);
    }

    m_followhud.draw(renderwindow);
    m_scale.draw(renderwindow);
    m_timehud.draw(renderwindow);
}


////////////////////////////////////////////////////////////////////////////////
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
            m_cameraposition.y += m_scale.getScaleFactor() * -5.0; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Down:
            m_cameraposition.y += m_scale.getScaleFactor() * 5.0; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Left:
            m_cameraposition.x += m_scale.getScaleFactor() * -5.0; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Right:
            m_cameraposition.x += m_scale.getScaleFactor() * 5.0; // TODO change this to frame time instead of a fixed value
            break;
        case sf::Keyboard::Add:
            m_timescale *= 2;
            break;
        case sf::Keyboard::F:
            toggleFollow();
            break;
            default: break;
        }
    }
    break;
        default: break;
    }
}


////////////////////////////////////////////////////////////////////////////////
// orbital elements from https://ssd.jpl.nasa.gov/txt/p_elem_t1.txt
void Space::createSolarSystem()
{
    m_timehud.setupTimeNow();

    float J2000 = 2451545.0;
    float JNow = sfSpace::Time::getJDNowUTC();
    float JDiff = JNow - J2000;

    OrbitalElementsMajorPlanet
    oemercury = { 0.38709893 * sfSpace::SI::AU, 0.20563069,
                  7.00487, 48.33167, 77.45645, 252.25084 },
    oevenus = { 0.72333566 * sfSpace::SI::AU, 0.00677672,
                3.39467605, 76.67984255, 131.60246718, 181.97909950},
    oeearth = { 1.00000102 * sfSpace::SI::AU, 0.0167086, 0.00005,
                -11.26064 , 102.94719, 100.46435},
    oemars = { 1.52371034 * sfSpace::SI::AU, 0.09339410, 1.84969142,
               49.55953891, -23.94362959, -4.55343205};

    OrbitalElementsAll
    changemars{ 0.00001847 * sfSpace::SI::AU / sfSpace::SI::cy,
                0.00007882 / sfSpace::SI::cy,
                -0.00813131 / sfSpace::SI::cy,
                -0.29257343 / sfSpace::SI::cy,
                0.44441088 / sfSpace::SI::cy},
    changevenus{ 0.00000390 * sfSpace::SI::AU / sfSpace::SI::cy,
                -0.00004107 / sfSpace::SI::cy,
                -0.00078890 / sfSpace::SI::cy,
                -0.27769418 / sfSpace::SI::cy,
                0.00268329 / sfSpace::SI::cy},
    changemercury{ 0.00000037 * sfSpace::SI::AU / sfSpace::SI::cy,
                   0.00001906 / sfSpace::SI::cy,
                  -0.00594749 / sfSpace::SI::cy,
                  -0.12534081 / sfSpace::SI::cy,
                   0.16047689 / sfSpace::SI::cy},
    changeearth{ 0.00000562 * sfSpace::SI::AU / sfSpace::SI::cy,
                -0.00004392 / sfSpace::SI::cy,
                -0.01294668 / sfSpace::SI::cy,
                 0.32327364 / sfSpace::SI::cy, 0.0},
    changemoon{0.0, 0.0, 0.0, -0.0529538083 / sfSpace::SI::d, 0.0,
               0.1643573223 / sfSpace::SI::d };

    OrbitalElementsSimple
    oemoon = { 384400000, 0.0554, 5.16, 125.08, 318.15, 135.27};

    CelestialBody* sun = new CelestialBody(1.989e30, 695.51e6, "Sun",
                                           sf::Color::Yellow);

    CelestialBody* mercury = new CelestialBody(3.28e23, 2.4397e6, "Mercury",
                                               sf::Color(128,128,128));

    CelestialBody* venus = new CelestialBody(4.867e24, 6051800 , "Venus",
                                             sf::Color(182,149,98));

    CelestialBody* earth = new CelestialBody(5.97237e24, 6378000 , "Earth",
                                             sf::Color::Green);

    CelestialBody* moon = new CelestialBody(7.342e22, 1738100 , "Moon",
                                            sf::Color(128,128,128));

    CelestialBody* mars = new CelestialBody(6.4171e23, 3389500 , "Mars",
                                             sf::Color::Red);

    mercury->setParent(sun);
    venus->setParent(sun);
    earth->setParent(sun);
    mars->setParent(sun);
    moon->setParent(earth);

    mercury->getOrbit()->setOrbitalElements(oemercury, changemercury);
    venus->getOrbit()->setOrbitalElements(oevenus, changevenus);
    earth->getOrbit()->setOrbitalElements(oeearth, changeearth);
    mars->getOrbit()->setOrbitalElements(oemars, changemars);
    moon->getOrbit()->setOrbitalElements(oemoon, changemoon);

    m_bodies.push_back(sun);
    m_bodies.push_back(mercury);
    m_bodies.push_back(venus);
    m_bodies.push_back(earth);
    m_bodies.push_back(mars);
    m_bodies.push_back(moon);

    advanceEpoch(JDiff);

    follow(sun);

    m_selectme = moon;
}


////////////////////////////////////////////////////////////////////////////////
Vector2D Space::translatePoint(Vector2D point)
{
    point -= m_cameraposition;

    point *= m_scale.getInvScaleFactor();

    return point;
}


////////////////////////////////////////////////////////////////////////////////
sfSpace::PRECISE Space::translateLength(sfSpace::PRECISE length)
{
    return length * m_scale.getInvScaleFactor();
}


////////////////////////////////////////////////////////////////////////////////
void Space::clearBodies()
{
    for (auto it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        delete *it;
    }
}


////////////////////////////////////////////////////////////////////////////////
void Space::lookAt(CelestialBody* lookatme)
{
    m_cameraposition = lookatme->getOrbit()->getGlobalPosition();
}


////////////////////////////////////////////////////////////////////////////////
void Space::follow(CelestialBody* object)
{
    m_followme = object;
    Space::follow();
}


////////////////////////////////////////////////////////////////////////////////
void Space::follow()
{
    m_isfollowing = true;

    m_followhud.follow(m_followme);
}


////////////////////////////////////////////////////////////////////////////////
void Space::unfollow()
{
    m_isfollowing = false;

    m_followhud.unfollow(m_followme);
}


////////////////////////////////////////////////////////////////////////////////
void Space::toggleFollow()
{
    if (m_isfollowing)
        m_followhud.unfollow(m_followme);
    else
        m_followhud.follow(m_followme);

    m_isfollowing = !m_isfollowing;
}


////////////////////////////////////////////////////////////////////////////////
bool Space::isFollowing() const
{
    return m_isfollowing;
}


////////////////////////////////////////////////////////////////////////////////
void Space::advanceEpoch(sfSpace::PRECISE epoch)
{
    for(auto it = m_bodies.begin();it != m_bodies.end();it++)
    {
        (*it)->getOrbit()->advanceMeanAnomaly(epoch * sfSpace::SI::d);
    }
}


////////////////////////////////////////////////////////////////////////////////
void Space::drawCircularObject(CelestialBody* obj, sf::RenderWindow* render)
{
    Vector2D pos = translatePoint(obj->getOrbit()->getGlobalPosition());
    auto radius = translateLength(obj->getRadius());

    if (pos.length() < render->getSize().x * 0.5 + radius) // TODO: bad rule -> objects around the corners don't render
    {
        // Draw it once the diameter reaches 1 px
        if (radius >= 0.5)
        {
            sf::CircleShape rendercircle;

            rendercircle.setRadius(radius);
            rendercircle.setFillColor(obj->getColor());
            rendercircle.setOrigin(radius, radius);
            rendercircle.setPosition(pos.x , pos.y);
            rendercircle.move(render->getSize().x * 0.5,
                              render->getSize().y * 0.5);

            render->draw(rendercircle);
        }
        else
        if (radius < 0.5)
        {
            sf::RectangleShape indicator(sf::Vector2f(10, 10));
            indicator.setFillColor(sf::Color::Transparent);
            indicator.setOutlineColor(sf::Color::White);
            indicator.setOutlineThickness(2);
            indicator.setOrigin(5, 5);
            indicator.setPosition(pos.x, pos.y);
            indicator.move(render->getSize().x * 0.5,render->getSize().y * 0.5);
            adjustToRaster(indicator);

            sf::Text label(obj->getName(),
                *ResourceManager::getInstance()->getFont("systemfont"), 16);
            label.setFillColor(sf::Color::White);
            label.setPosition(pos.x - 10 - label.getLocalBounds().width,
                              pos.y - 5 - label.getLocalBounds().height);
            label.move(render->getSize().x * 0.5,render->getSize().y * 0.5);
            adjustToRaster(label);

            render->draw(indicator);
            render->draw(label);

            if (m_selectme == obj)
            {
                sf::Text ot(obj->getOrbit()->orbitalElementsToString(),
                *ResourceManager::getInstance()->getFont("systemfont"), 16);

                ot.setFillColor(sf::Color::White);
                ot.setPosition(pos.x + 10,  pos.y - 15);
                ot.move(render->getSize().x * 0.5, render->getSize().y * 0.5);

                adjustToRaster(ot);

                render->draw(ot);
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
void Space::adjustToRaster(sf::Transformable& object)
{
    object.setPosition(std::floor(object.getPosition().x),
                       std::floor(object.getPosition().y));
}
