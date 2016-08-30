#include "solarsystem.h"

solarSystem::~solarSystem()
{
}

vector<Galaxy> solarSystem::getParent()
{
    return m_parent;
}
