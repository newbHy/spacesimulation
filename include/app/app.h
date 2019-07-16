#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "app/cerrredirect.h"
#include "states/statemanager.h"



class App final
{
    public:
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        App(unsigned int width, unsigned int height, sf::String title);
        ~App();

        // Runs this application until it's closed by the user
        bool run();

        // Forces closure
        void close();

        // Sets the frame limit for both graphical fps and logical fps
        void setFrameLimit(unsigned int frames, unsigned int logicframes);

    private:
        sf::RenderWindow m_renderwindow;

        bool             m_running;

        StateManager     m_statemanager;

        // Frame control
        sf::Clock        m_timer;               // This is basically the uptime of the application
        float            m_frameaccumulator;    // Gathers frame time for the logic updater
        float            m_framenow;            // Always
        float            m_frametime;           // FPS inversed
        float            m_frametimelogic;      // LFPS inversed

        CerrRedirect     cerrredirect;
};

#endif // APP_H
