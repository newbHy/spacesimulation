#include "space/orbit.h"

#include <math.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "misc/conversions.h"
#include "misc/stringoperations.h"
#include "si/metrics.h"
#include "space/celestialbody.h"



////////////////////////////////////////////////////////////////////////////////
Orbit::Orbit(CelestialBody* owner)
  : m_owner(owner),
    m_orbitType(Orbit::OrbitType::barrycenter)
{
    // ...
    m_rateofchange = {0};
}


////////////////////////////////////////////////////////////////////////////////
Orbit::~Orbit()
{
    // ...
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::update(float time)
{
    if (m_orbitType == Orbit::OrbitType::fixed)
    {
        adjustOrbitalElements(time);

        advanceMeanAnomaly(time);

        calculateEccentricAnomaly();

        calculatePosition();
    }
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::advanceMeanAnomaly(float time)
{
    adjustOrbitalElements(time);

    m_M = std::fmod(m_M + 360.0 * (time * m_period_inv), 360.0);
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::calculatePeriod()
{
    if (m_orbitType == Orbit::OrbitType::fixed &&
        m_owner != nullptr && m_owner->getParent() != nullptr)
    {
        m_period = 2 * sfSpace::Pi * sqrt( pow(m_a, 3) /
                   (m_owner->getParent()->getMass() * sfSpace::G) );
        m_period_inv = 1.0 / m_period;

#ifdef DEBUG
        std::cerr << "[Orbital element] <" << m_owner->getName().toAnsiString()
                  << ">s period is " << m_period / sfSpace::SI::d << " days"
                  << std::endl;
#endif // DEBUG
    }
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::setOrbitalElements(OrbitalElementsMajorPlanet &data,
                               OrbitalElementsAll rateofchange)
{
    m_a = data.a;
    m_e = data.e;
    m_i = data.i;
    m_N = data.N;
    m_w1 = data.w1;

    m_w = data.w1 - data.N;
    m_M = std::fmod(data.L - data.w1, 360.0);

    if (m_e > 0.0)
    {
        m_b = m_a * sqrt(1.0 - m_e * m_e);
    }

#ifdef DEBUG
    std::cerr << "[Orbital element] <" << m_owner->getName().toAnsiString()
              << ">s orbital elements are: " << m_a << " " << m_e << " "
              << m_i << " " << m_M << " " << m_N << " " << m_w
              << std::endl;
#endif // DEBUG

    calculatePeriod();

    m_rateofchange = rateofchange;
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::setOrbitalElements(OrbitalElementsSimple &data,
                               OrbitalElementsAll rateofchange)
{
    m_a = data.a;
    m_e = data.e;
    m_i = data.i;
    m_N = data.N;
    m_w = data.w;
    m_M = data.M;

    if (m_e > 0.0)
    {
        m_b = m_a * sqrt(1.0 - m_e * m_e);
    }

    calculatePeriod();

    m_rateofchange = rateofchange;
}


////////////////////////////////////////////////////////////////////////////////
// credits: 1 ) http://www.jgiesen.de/kepler/kepler.html
//          2 ) Fundamentals of Astrodynamics and Applications by David A. Vallado (Autor)
void Orbit::calculateEccentricAnomaly(unsigned int precision)
{
    unsigned int maxIter=30, i=0;

    sfSpace::PRECISE delta = 1.0 / pow(10,precision);

    sfSpace::PRECISE E, F, M;

    M = m_M * sfSpace::degtoRad;

    if (m_e < 0.8)
        E = M;
    else
        E = sfSpace::Pi;

    F = E - m_e * sin(M) - M;

    while ((fabs(F) > delta) && (i < maxIter))
    {
        E = E - F / (1.0 - m_e * cos(E));
        F = E - m_e * sin(E) - M;

        i = i + 1;
    }

    m_E = round(E * pow(10, precision))/ pow(10, precision);
}


////////////////////////////////////////////////////////////////////////////////
// Credits: 1 ) https://stjarnhimlen.se/comp/ppcomp.html#4
void Orbit::calculatePosition()
{
    sfSpace::PRECISE xv, yv;

    xv = m_a * (cos (m_E) - m_e);
    yv = m_b * sin(m_E);

    m_v = atan2(yv, xv);
    m_r = sqrt(xv*xv + yv*yv);

    sfSpace::PRECISE i = m_i * sfSpace::degtoRad,
                     N = m_N * sfSpace::degtoRad,
                     w = m_w * sfSpace::degtoRad;

    m_position.x = m_r * (cos(N) * cos(m_v+w) - sin(N) * sin(m_v+w) * cos(i));
    m_position.y = m_r * (sin(N) * cos(m_v+w) + cos(N) * sin(m_v+w) * cos(i));
    m_position.z = m_r * (sin(m_v+w) * sin(i));
}


////////////////////////////////////////////////////////////////////////////////
Vector Orbit::getGlobalPosition() const
{
    if (m_owner->getParent())
        return m_position
             + m_owner->getParent()->getOrbit()->getGlobalPosition();

    return m_position;
}


////////////////////////////////////////////////////////////////////////////////
Orbit::OrbitType Orbit::getOrbitType() const
{
    return m_orbitType;
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::setOrbitType(Orbit::OrbitType type)
{
    m_orbitType = type;
}


////////////////////////////////////////////////////////////////////////////////
void Orbit::adjustOrbitalElements(float time)
{
    m_a  = m_a + m_rateofchange.a * time;
    m_e  = m_e + m_rateofchange.e * time;
    m_i  = fmod(m_i + m_rateofchange.i * time, 360);
    m_N  = fmod(m_N + m_rateofchange.N * time, 360);
    m_w1 = fmod(m_w1 + m_rateofchange.w1 * time, 360);
    m_w = fmod(m_w + m_rateofchange.w * time, 360);

    if (m_rateofchange.w1)
    {
        m_w = fmod(m_w1 - m_N, 360);
    }
}


////////////////////////////////////////////////////////////////////////////////
std::string Orbit::orbitalElementsToString() const
{
    std::string str;

    str = "a : " + to_string_with_precision(m_a / sfSpace::SI::AU, 2) +
          " AU\n" +
          "e : " + to_string_with_precision(m_e) + "\n" +
          "i : " + to_string_with_precision(m_i, 4) + "\n" +
          "N : " + to_string_with_precision(m_N, 4) + "\n" +
          "w : " + to_string_with_precision(m_w, 4) + "\n" +
          "M : " + to_string_with_precision(m_M, 4);

    return str;
}
