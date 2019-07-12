#ifndef TIMEHUD_H
#define TIMEHUD_H

#include <SFML/Graphics/Text.hpp>
#include "typedefs.h"



class TimeHud
{
    public:
        TimeHud();
        virtual ~TimeHud();

        void draw(sf::RenderWindow* renderwindow);

        const sfSpace::PRECISE getTimeModifier() const;

    protected:

    private:

        sfSpace::PRECISE    m_timemodifier;
        sf::Text            m_timetext;
};

#endif // TIMEHUD_H
