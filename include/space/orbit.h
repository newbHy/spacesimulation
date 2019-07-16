#ifndef ORBIT_H
#define ORBIT_H

#include <string>

#include "misc/typedefs.h"
#include "misc/vector.h"
#include "space/orbitalelements.h"



class CelestialBody;

class Orbit final
{
    public:
        enum class OrbitType { free, fixed, barrycenter };

        Orbit(CelestialBody* owner);

        ~Orbit();

        void update(float time);

        // Sets the orbital elements (for major planets)
        void setOrbitalElements(OrbitalElementsMajorPlanet &data,
                                OrbitalElementsAll rateofchange = {0} );

        // For satelites and comets
        void setOrbitalElements(OrbitalElementsSimple &data,
                                OrbitalElementsAll rateofchange = {0});

        // Returns the global position
        Vector getGlobalPosition() const;

        // Returns the orbit type
        OrbitType getOrbitType() const;

        // Sets the orbit type
        void setOrbitType(OrbitType type);

        // Advances the mean anomaly by the given amount of time (in seconds)
        void advanceMeanAnomaly(float time);

        std::string orbitalElementsToString() const;

    private:
        // Calculates the period
        // Note: only possible if a parent is given beforehand
        void calculatePeriod();

        // Uses the rate of change to update the orbital elements
        void adjustOrbitalElements(float time);

        // Calculates the eccentric anomaly for this orbit
        void calculateEccentricAnomaly(unsigned int precision = 7);

        // Calculates the current position for this celestial body
        void calculatePosition();

        // This orbit belongs to this celestial body
        CelestialBody*      m_owner;

        // Primary orbital elements
        sfSpace::PRECISE    m_N,              // longitude of the ascending node
                            m_i,              // inclination to the ecliptic
                            m_w,              // argument of perihelion
                            m_a,              // semimajor axis
                            m_e,              // eccentricity
                            m_M;              // mean anomaly (in deg)

        // Secondary orbital elements
        sfSpace::PRECISE    m_period,         // period
                            m_period_inv,     // period inversed
                            m_w1,             // argument of periphelion
                            m_E,              // eccentric anomaly (in rad)
                            m_v,              // true anomaly (in rad)
                            m_r,              // distance to parent (in m)
                            m_b;              // semi minor axis (in m)

        Vector              m_position;       // 3D position (local if parent is given)

        OrbitalElementsAll  m_rateofchange;

        Orbit::OrbitType    m_orbitType;
};

#endif // ORBIT_H

// sources:
// http://www.jgiesen.de/kepler/kepler.html
// https://www.aa.quae.nl/en/reken/zonpositie.html
// https://stjarnhimlen.se/comp/ppcomp.html#4
// https://ssd.jpl.nasa.gov/horizons.cgi#results
