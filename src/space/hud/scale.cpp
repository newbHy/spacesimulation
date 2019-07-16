#include "space/hud/scale.h"

#include <SFML/Graphics.hpp>

#include "assets/resourcemanager.h"
#include "misc/stringoperations.h"
#include "si/metrics.h"



////////////////////////////////////////////////////////////////////////////////
Scale::Scale()
  : m_scalewidth(50)
{
    setScaleFactor((0.33 * sfSpace::SI::AU) / m_scalewidth);

    m_scaletext.setFillColor(sf::Color::White);
    m_scaletext.setCharacterSize(16);
    m_scaletext.setPosition(10,10);

    if (ResourceManager::getInstance()->loadFont("coders_crux.ttf",
                                                                  "systemfont"))
    {
        m_scaletext.setFont(*ResourceManager::getInstance()->
                                                         getFont("systemfont"));
    }

    updateScaleText();
}


////////////////////////////////////////////////////////////////////////////////
Scale::~Scale()
{
    // ...
}


////////////////////////////////////////////////////////////////////////////////
void Scale::draw(sf::RenderWindow* renderwindow)
{
    sf::VertexArray scalegfx(sf::LineStrip, 4);

    scalegfx[0].position = sf::Vector2f(25, renderwindow->getSize().y - 40);
    scalegfx[1].position = sf::Vector2f(25, renderwindow->getSize().y - 25);
    scalegfx[2].position = sf::Vector2f(25 + m_scalewidth,
                                             renderwindow->getSize().y - 25);
    scalegfx[3].position = sf::Vector2f(25 + m_scalewidth,
                                             renderwindow->getSize().y - 40);

    for(int i = 0;i < 4;++i)
        scalegfx[i].color = sf::Color::White;

    m_scaletext.setPosition(25, renderwindow->getSize().y - 25);

    renderwindow->draw(scalegfx);
    renderwindow->draw(m_scaletext);
}


////////////////////////////////////////////////////////////////////////////////
sfSpace::PRECISE Scale::getScaleFactor() const
{
    return m_scalefactor;
}


////////////////////////////////////////////////////////////////////////////////
sfSpace::PRECISE Scale::getInvScaleFactor() const
{
    return m_scalefactorinv;
}


////////////////////////////////////////////////////////////////////////////////
void Scale::setScaleFactor(sfSpace::PRECISE factor)
{
    m_scalefactor = factor;

    if (m_scalefactor < 1)
        m_scalefactor = 1;
    if (m_scalefactor > sfSpace::SI::AU * 0.5)
        m_scalefactor = sfSpace::SI::AU * 0.5;

    m_scalefactorinv = 1.0 / m_scalefactor;
}


////////////////////////////////////////////////////////////////////////////////
void Scale::updateScaleText()
{
    auto scalemodified = m_scalefactor * m_scalewidth;

    if (scalemodified < 15 * sfSpace::SI::KM) // Show meters below 15km
    {
        m_scaletext.setString(to_string_with_precision
                              (scalemodified, 2) + " m");
    }
    else
    if (scalemodified < 0.25 * sfSpace::SI::LD) // Show kilometers below 0.25LD
    {
        m_scaletext.setString(to_string_with_precision(
                              scalemodified * 0.001, 2) + " km");
    }
    else
    if (scalemodified < 0.05 * sfSpace::SI::AU) // Show lunar distances below 0.05AU
    {
        m_scaletext.setString(to_string_with_precision(
                              scalemodified / sfSpace::SI::LD, 2) + " LD");
    }
    else
    {
        m_scaletext.setString(to_string_with_precision(
                              scalemodified / sfSpace::SI::AU, 2) + " AU");
    }
}
