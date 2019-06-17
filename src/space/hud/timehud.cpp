#include <SFML/Graphics.hpp>

#include "assets/resourcemanager.h"
#include "misc/stringoperations.h"
#include "space/timefunctions.h"
#include "timehud.h"



///////////////////////////////////////////////////////////////////////////////
TimeHud::TimeHud() : m_timemodifier(1.0)
{
    m_timetext.setFillColor(sf::Color::White);
    m_timetext.setCharacterSize(16);
    m_timetext.setPosition(10,10);

    m_timetext.setFont(*ResourceManager::getInstance()->getFont("systemfont"));
}


///////////////////////////////////////////////////////////////////////////////
TimeHud::~TimeHud()
{
    //dtor
}


///////////////////////////////////////////////////////////////////////////////
void TimeHud::draw(sf::RenderWindow* renderwindow)
{
    m_timetext.setString(getTimeStr());

    setOriginTopLeft(m_timetext);

    m_timetext.setPosition(renderwindow->getSize().x - m_timetext.getLocalBounds().width,
                           renderwindow->getSize().y - m_timetext.getLocalBounds().height);


    renderwindow->draw(m_timetext);
}


///////////////////////////////////////////////////////////////////////////////
const sfSpace::PRECISE TimeHud::getTimeModifier() const
{
    return m_timemodifier;
}
