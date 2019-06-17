#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "states/statemanager.h"
#include "cerrredirect.h"



class App
{
    public:
        App(unsigned int width, unsigned int height, sf::String title);
        virtual ~App();

        bool run();

        void close();

        void setFrameLimit(unsigned int frames, unsigned int logicframes);

    protected:

    private:

        void doFrame();

        sf::RenderWindow m_renderwindow;

        bool             m_running;

        StateManager     m_statemanager;

        sf::Clock        m_timer;
        float            m_frameaccumulator;    // gathers frame time for the logic updater
        float            m_framenow;
        float            m_frametime;           // FPS inversed
        float            m_frametimelogic;      // LFPS inversed

        CerrRedirect     cerrredirect;
};

#endif // APP_H
