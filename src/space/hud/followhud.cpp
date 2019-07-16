#include "space/hud/followhud.h"

#include <math.h>

#include <SFML/Graphics.hpp>

#include "assets/resourcemanager.h"
#include "misc/stringoperations.h"
#include "si/metrics.h"



////////////////////////////////////////////////////////////////////////////////
FollowHud::FollowHud()
 : m_isfollowing(false)
{
    if (ResourceManager::getInstance()->loadFont("coders_crux.ttf",
                                                                  "systemfont"))
    {
        m_followtext.setFont(*ResourceManager::getInstance()->
                                                         getFont("systemfont"));

        m_followtext.setFillColor(sf::Color::White);
        m_followtext.setCharacterSize(16);
        m_followtext.setPosition(10,10);
    }
}


////////////////////////////////////////////////////////////////////////////////
FollowHud::~FollowHud()
{
    // ...
}


////////////////////////////////////////////////////////////////////////////////
void FollowHud::draw(sf::RenderWindow* renderwindow)
{
    if (!m_isfollowing)
    {
        float time = m_timer.getElapsedTime().asSeconds();

        if (time > 1.5f && time < 2.5f)
        {
            setAlpha(2.5f - time);
        }
        else
        if (time > 2.5f)
        {
            setAlpha(0.f);
        }
    }

    renderwindow->draw(m_followtext);
}


////////////////////////////////////////////////////////////////////////////////
void FollowHud::follow(CelestialBody* object)
{
    m_followtext.setString("Following " + object->getName() + " (F)");
    m_isfollowing = true;

    setAlpha(1.f);
}


////////////////////////////////////////////////////////////////////////////////
void FollowHud::unfollow(CelestialBody* object)
{
    m_followtext.setString("Unfollowed " + object->getName());
    m_timer.restart();
    m_isfollowing = false;
}


////////////////////////////////////////////////////////////////////////////////
void FollowHud::setAlpha(float rate)
{
    sf::Color color = m_followtext.getFillColor();
    color.a = 255 * rate;

    m_followtext.setFillColor(color);
}
