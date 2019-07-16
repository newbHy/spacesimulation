#ifndef SCALE_H
#define SCALE_H

#include <SFML/Graphics/Text.hpp>

#include "misc/typedefs.h"



namespace sf
{
    class RenderWindow;
}

class Scale
{
    public:
        Scale();
        ~Scale();

        void draw(sf::RenderWindow* renderwindow);

        sfSpace::PRECISE getScaleFactor() const;

        sfSpace::PRECISE getInvScaleFactor() const;

        void setScaleFactor(sfSpace::PRECISE factor);

        // Updates the text to display the correct scale factor
        void updateScaleText();

    private:
        sfSpace::PRECISE  m_scalefactor;
        sfSpace::PRECISE  m_scalefactorinv;

        sf::Text          m_scaletext;

        int               m_scalewidth;
};

#endif // SCALE_H
