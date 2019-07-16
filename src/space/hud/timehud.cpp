#include "space/hud/timehud.h"

#include <SFML/Graphics.hpp>

#include "assets/resourcemanager.h"
#include "misc/stringoperations.h"
#include "space/timefunctions.h"



////////////////////////////////////////////////////////////////////////////////
TimeHud::TimeHud()
  : m_timemodifier(1.0),
    m_timestamp(0),
    m_timestampreminder(0.f)
{
    m_timetext.setFillColor(sf::Color::White);
    m_timetext.setCharacterSize(16);
    m_timetext.setPosition(10,10);

    m_timetext.setFont(*ResourceManager::getInstance()->getFont("systemfont"));
}


////////////////////////////////////////////////////////////////////////////////
TimeHud::~TimeHud()
{
    // ...
}


////////////////////////////////////////////////////////////////////////////////
void TimeHud::draw(sf::RenderWindow* renderwindow)
{
    m_timetext.setString(sfSpace::Time::getTimeStr(m_timestamp));

    setOriginTopLeft(m_timetext);

    m_timetext.setPosition(
               renderwindow->getSize().x - m_timetext.getLocalBounds().width,
               renderwindow->getSize().y - m_timetext.getLocalBounds().height);


    renderwindow->draw(m_timetext);
}


////////////////////////////////////////////////////////////////////////////////
void TimeHud::advanceTime(float time)
{
    m_timestampreminder += time;

    if (m_timestampreminder >= 1.f)
    {
        unsigned int seconds = m_timestampreminder;
        m_timestamp += seconds;
        m_timestampreminder -= seconds;
    }
}


////////////////////////////////////////////////////////////////////////////////
void TimeHud::setupTimeNow()
{
    m_timestamp = sfSpace::Time::now();
    m_timestampreminder = 0.f;
}
