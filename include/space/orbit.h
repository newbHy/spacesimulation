#ifndef ORBIT_H
#define ORBIT_H

#include "typedefs.h"
#include "vector.h"



class CelestialBody;

class Orbit
{
    public:

        enum class OrbitType { free, fixed };

        Orbit(CelestialBody* owner);
        virtual ~Orbit();

        void update(float time);
        void setOrbitalElements(sfSpace::PRECISE a, sfSpace::PRECISE e, sfSpace::PRECISE M,
                                sfSpace::PRECISE N, sfSpace::PRECISE i, sfSpace::PRECISE w);

        Vector getGlobalPosition() const;

    protected:
        void calculatePeriod();
        void setMeanAnomaly();

        // Calculate the eccentric anomaly for this orbit
        void calculateEccentricAnomaly(unsigned int precision = 5);

        // Calculate the current position for this celestial body
        void calculatePosition();

    private:


        CelestialBody*      m_owner;

        // Primary orbital elements
        sfSpace::PRECISE    m_N,              // longitude of the ascending node
                            m_i,              // inclination to the ecliptic
                            m_w,              // argument of perihelion
                            m_a,              // semimajor axis
                            m_e,              // eccentricity
                            m_M;              // mean anomaly

        // Secondary orbital elements
        sfSpace::PRECISE    m_period,         // period
                            m_period_inv,     // period inversed
                            m_E,              // eccentric anomaly
                            m_v,              // true anomaly
                            m_r,              // distance to parent
                            m_b;              // semi minor axis
        Vector              m_position;       // 3D position (local if parent is given)


        Orbit::OrbitType    m_orbitType;
};

#endif // ORBIT_H

// sources:
// http://www.jgiesen.de/kepler/kepler.html
// https://www.aa.quae.nl/en/reken/zonpositie.html
// https://stjarnhimlen.se/comp/ppcomp.html#4
