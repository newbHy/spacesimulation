#include "app/app.h"

#ifdef DEBUG
    #include <iostream>
    #include <math.h>
#endif // DEBUG

#include "space/simulationstate.h"



////////////////////////////////////////////////////////////////////////////////
App::App(unsigned int width, unsigned int height, sf::String title)
  : m_renderwindow(sf::VideoMode(width, height), title),
    m_running(true),
    m_statemanager(),
    m_timer(),
    m_frameaccumulator(0.f),
    m_framenow(0.f),
    m_frametime(0.f),
    m_frametimelogic(0.f),
    cerrredirect()
{
    setFrameLimit(30, 15);

    m_statemanager.changeState(&SimulationState::getInstance());
}


////////////////////////////////////////////////////////////////////////////////
App::~App()
{
#ifdef DEBUG
    std::cerr << "[Shutdown] Time : "
              << std::floor(m_timer.getElapsedTime().asSeconds())
              << " seconds" << std::endl;
#endif
}


////////////////////////////////////////////////////////////////////////////////
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
        // Accumulator from:
        // http://gafferongames.com/game-physics/fix-your-timestep/
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


////////////////////////////////////////////////////////////////////////////////
void App::close()
{
    m_running = false;
}


////////////////////////////////////////////////////////////////////////////////
void App::setFrameLimit(unsigned int frames, unsigned int logicframes)
{
    m_frametime      = static_cast<float>(1.f / frames);
    m_frametimelogic = static_cast<float>(1.f / logicframes);
}
