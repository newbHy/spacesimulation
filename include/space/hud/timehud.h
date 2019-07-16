#ifndef TIMEHUD_H
#define TIMEHUD_H

#include <SFML/Graphics/Text.hpp>

#include "misc/typedefs.h"



namespace sf
{
    class RenderWindow;
}

class TimeHud final
{
    public:
        TimeHud();
        ~TimeHud();

        void draw(sf::RenderWindow* renderwindow);

        void advanceTime(float time);

        void setupTimeNow();

    private:
        sfSpace::PRECISE    m_timemodifier;

        sf::Text            m_timetext;

        std::time_t         m_timestamp;

        float               m_timestampreminder;
};

#endif // TIMEHUD_H
