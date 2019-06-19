#ifndef SCALE_H
#define SCALE_H

#include <SFML/Graphics/Text.hpp>

#include "misc/typedefs.h"



class Scale
{
    public:
        Scale();
        virtual ~Scale();

        void draw(sf::RenderWindow* renderwindow);

        sfSpace::PRECISE getScaleFactor() const;
        sfSpace::PRECISE getInvScaleFactor() const;

        void setScaleFactor(sfSpace::PRECISE factor);
        void updateScaleText();

    private:

        sfSpace::PRECISE    m_scalefactor;
        sfSpace::PRECISE    m_scalefactorinv;

        sf::Text            m_scaletext;

        unsigned int        m_scalewidth;
};

#endif // SCALE_H
