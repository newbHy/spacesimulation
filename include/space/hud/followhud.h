#ifndef FOLLOWHUD_H
#define FOLLOWHUD_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "misc/typedefs.h"
#include "space/celestialbody.h"



namespace sf
{
    class RenderWindow;
}

class FollowHud
{
    public:
        FollowHud();
        ~FollowHud();

        void draw(sf::RenderWindow* renderwindow);

        void follow(CelestialBody* object);

        void unfollow(CelestialBody* object);

    private:
        // Sets the alpha value of the text. Range of rate is 0..1
        void setAlpha(float rate);

        sf::Text  m_followtext;
        sf::Clock m_timer;
        bool      m_isfollowing;
};

#endif // FOLLOWHUD_H
