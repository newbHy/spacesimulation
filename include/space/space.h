#ifndef SPACE_H
#define SPACE_H

#include "hud/followhud.h"
#include "hud/scale.h"
#include "hud/timehud.h"
#include "misc/vector.h"
#include "space/celestialbody.h"



namespace sf
{
class RenderWindow;
class Event;
}

class Space
{
    public:
        typedef std::vector<CelestialBody*> CBVector;

        Space(const Space& rhs) = delete;
        Space& operator=(const Space& rhs) = delete;

        Space();
        virtual ~Space();

        void onUpdate(float time);

        void onDraw(sf::RenderWindow* renderwindow);

        void onEvent(sf::Event& event);

        void createSolarSystem();

        // Translates a world coordinate to screen coordinate
        Vector2D translatePoint(Vector2D point);

        // Translates a world length to screen length
        sfSpace::PRECISE translateLength(sfSpace::PRECISE length);

        void clearBodies();

    private:
        // Advances all orbital elements of all celestial bodies with the given
        // time interval
        void advanceEpoch(sfSpace::PRECISE epoch);

        // Adjusts text in such a way that it aligns with the pixel raster
        inline void adjustToRaster(sf::Transformable& textobject);

        // Centers the camera to this object
        void lookAt(CelestialBody* lookatme);

        // Follows this object
        void follow(CelestialBody* follow);

        // Follows the unfollowed object
        void follow();

        // Stops following the object currently marked as a follow-object
        void unfollow();

        void toggleFollow();

        // Checks whever the camera is following an object
        inline bool isFollowing() const;

        // Draws celestial bodies
        void drawCircularObject(CelestialBody* obj, sf::RenderWindow* render);

        Scale          m_scale;
        TimeHud        m_timehud;
        FollowHud      m_followhud;

        int            m_timescale;

        Vector2D       m_cameraposition;

        CBVector       m_bodies;
        CelestialBody* m_followme;
        CelestialBody* m_selectme;

        bool           m_isfollowing;
};

#endif // SPACE_H
