#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

#include "typedefs.h"
#include "orbit.h"



class CelestialBody
{
    public:
        CelestialBody();
        CelestialBody(sfSpace::PRECISE mass, sfSpace::PRECISE radius, sf::String name, sf::Color color);

        virtual ~CelestialBody();

        Orbit* getOrbit();

        void setParent(CelestialBody* parent);

        CelestialBody* getParent() const;

        void setMass(sfSpace::PRECISE mass);

        sfSpace::PRECISE getMass() const;

        void setRadius(sfSpace::PRECISE radius);

        sfSpace::PRECISE getRadius() const;

        void setName(sf::String name);

        sf::String getName() const;

        void setColor(sf::Color color);

        sf::Color getColor() const;

    private:
        sfSpace::PRECISE    m_mass;         // mass in kg
        sfSpace::PRECISE    m_radius;       // radius in m

        CelestialBody*      m_parent;
        Orbit               m_orbit;

        sf::String          m_name;
        sf::Color           m_color;
};

#endif // CELESTIALBODY_H
