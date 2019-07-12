#include <math.h>

#include "celestialbody.h"
#include "conversations.h"
#include "orbit.h"
#include "metrics.h"



///////////////////////////////////////////////////////////////////////////////
Orbit::Orbit(CelestialBody* owner) : m_owner(owner),
    m_orbitType(Orbit::OrbitType::fixed)
{

}


///////////////////////////////////////////////////////////////////////////////
Orbit::~Orbit()
{
    //dtor
}


///////////////////////////////////////////////////////////////////////////////
void Orbit::update(float time)
{
    if (m_orbitType == Orbit::OrbitType::fixed)
    {
        m_M += 360.0 * (time * m_period_inv);
        if (m_M >= 360.0)
            m_M -= 360.0;

        calculateEccentricAnomaly();

        calculatePosition();
    }
}


///////////////////////////////////////////////////////////////////////////////
void Orbit::setMeanAnomaly()
{

}


///////////////////////////////////////////////////////////////////////////////
void Orbit::calculatePeriod()
{
    if (m_orbitType == Orbit::OrbitType::fixed &&
        m_owner != nullptr && m_owner->getParent() != nullptr)
    {
        m_period = 2 * sfSpace::Pi * sqrt( pow(m_a, 3) / (m_owner->getParent()->getMass() * sfSpace::G) );
        m_period_inv = 1.0 / m_period;
    }
}


///////////////////////////////////////////////////////////////////////////////
void Orbit::setOrbitalElements(sfSpace::PRECISE a, sfSpace::PRECISE e, sfSpace::PRECISE M, sfSpace::PRECISE N, sfSpace::PRECISE i, sfSpace::PRECISE w)
{
    m_a = a;
    m_e = e;
    m_M = M;
    m_N = N;
    m_i = i;
    m_w = w;

    if (a > 0.0)
    {
        if (e != 1.0)
            m_b = m_a * sqrt(1.0 - e * e);
        else
            m_b = m_a;
    }

    calculatePeriod();
}


///////////////////////////////////////////////////////////////////////////////
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

    E = E * sfSpace::radtoDeg;

    m_E = round(E * pow(10, precision))/ pow(10, precision);
}


///////////////////////////////////////////////////////////////////////////////
// Credits: 1 ) https://stjarnhimlen.se/comp/ppcomp.html#4
void Orbit::calculatePosition()
{
    sfSpace::PRECISE xv, yv;

    xv = m_a * (cos (m_E) - m_e);
    yv = m_b * sin(m_E);

    m_v = atan2(yv, xv);
    m_r = sqrt(xv*xv + yv*yv);

    m_position.x = m_r * (cos(m_N) * cos(m_v+m_w) - sin(m_N) * sin(m_v+m_w) * cos(m_i));
    m_position.y = m_r * (sin(m_N) * cos(m_v+m_w) + sin(m_N) * sin(m_v+m_w) * cos(m_i));
    m_position.z = m_r * (sin(m_v+m_w) * sin(m_i));
}


///////////////////////////////////////////////////////////////////////////////
Vector Orbit::getGlobalPosition() const
{
    return m_position;
}
