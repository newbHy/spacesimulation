#ifdef DEBUG
    #include <iostream>
#endif // DEBUG

#include <math.h>
#include "app.h"
#include "simulationstate.h"



///////////////////////////////////////////////////////////////////////////////
App::App(unsigned int width, unsigned int height, sf::String title)
{
    m_renderwindow.create(sf::VideoMode(width, height), title);

    setFrameLimit(60, 60);

    m_statemanager.changeState(&SimulationState::getInstance());
}


///////////////////////////////////////////////////////////////////////////////
App::~App()
{
    //dtor
#ifdef DEBUG
    std::cerr << "[Shutdown] Time : " << floor(m_timer.getElapsedTime().asSeconds()) << " seconds" << std::endl;
#endif // DEBUG
}


///////////////////////////////////////////////////////////////////////////////
bool App::run()
{
    if (!m_renderwindow.isOpen())
        return false;

    sf::Event event;

    m_running = true;
    m_frameaccumulator = 0.f;
    m_framenow = 0.f;
    m_timer.restart();

    while(m_running)
    {
        float newtime   = m_timer.getElapsedTime().asSeconds();
        float frametime = newtime - m_framenow;
        m_framenow      = newtime;

        m_frameaccumulator += frametime;

        while (m_renderwindow.pollEvent(event))
        {
            m_statemanager.onEvent(event);

            if (event.type == sf::Event::Closed)
                close();
        }

        m_renderwindow.clear();

        while (m_frameaccumulator >= m_frametimelogic)
        {
            m_frameaccumulator -= m_frametimelogic;
            m_statemanager.onUpdate(m_frametimelogic);
        }

        m_statemanager.onDraw(&m_renderwindow);

        m_renderwindow.display();

        while (m_timer.getElapsedTime().asSeconds() - newtime < m_frametime)
        {
            sf::sleep(sf::milliseconds(1));
        }
    }

    if (m_renderwindow.isOpen()) m_renderwindow.close();

    return true;
}


///////////////////////////////////////////////////////////////////////////////
void App::doFrame()
{
}


///////////////////////////////////////////////////////////////////////////////
void App::close()
{
    m_running = false;
}


///////////////////////////////////////////////////////////////////////////////
void App::setFrameLimit(unsigned int frames, unsigned int logicframes)
{
    m_frametime      = static_cast<float>(1.f / frames);
    m_frametimelogic = static_cast<float>(1.f / logicframes);
}
