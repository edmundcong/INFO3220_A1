#include <cmath>

#include "body.h"
#include "debug.h"

#include <stdio.h>

// This is auto-created by getTypicalInstance() when it is needed
Body* Body::typicalInstance = nullptr;

Body* Body::clone()
{
  return new Body(m_mass,
                  m_radius,
                  m_xPosition,
                  m_yPosition,
                  m_xVelocity,
                  m_yVelocity);
}

Body* Body::getTypicalInstance()
{
  // Create our prototypical instance if it doesn't exist
  if (Body::typicalInstance == nullptr)
  {
    Body::typicalInstance = new Body(1,1,0,0,0,0);
  }
  // Now just return it
  return Body::typicalInstance;
}

double Body::getDistance(const Body &other) const
{
  double xDelta = other.getXPosition() - m_xPosition;
  double yDelta = other.getYPosition() - m_yPosition;
  double distance =  sqrt(xDelta * xDelta + yDelta * yDelta);
  return distance;
}

void Body::addAttraction(const Body &other, double &xForce, double &yForce)
{
  double distance = getDistance(other);
  double xDelta = other.getXPosition() - m_xPosition;
  double yDelta = other.getYPosition() - m_yPosition;
  double theta = atan2(yDelta, xDelta);
  double force = G * m_mass * other.getMass() / (distance * distance);
  xForce += force * cos(theta);
  yForce += force * sin(theta);
}

void Body::update(double xTotalForce, double yTotalForce, double timestep)
{
  // calculate acceleration
  double xAccel = xTotalForce / m_mass;
  double yAccel = yTotalForce / m_mass;

  // integrate acceleration
  m_xVelocity += xAccel * timestep;
  m_yVelocity += yAccel * timestep;

  // integrate velocity
  m_xPosition += m_xVelocity * timestep;
  m_yPosition += m_yVelocity * timestep;
}

bool Body::getRenderName() const
{
  return m_renderName;
}

void Body::setRenderName(bool renderName)
{
  m_renderName = renderName;
}

bool Body::getBlackHoleValue() const
{
    return m_blackHole;
}
void Body::setBlackHole(bool blackHole){
    m_blackHole = blackHole;
}

bool Body::getContainerValue() const
{
    return m_container;
}

void Body::setContainerValue(bool container)
{
    m_container = container;
}

void Body::setSunValue(bool sun)
{
    m_sun = sun;
}

bool Body::getSunValue() const
{
    return m_sun;
}

Body::~Body()
{
  DEBUG("Body destructor");

  // delete the singular typical instance if it exists
  // other Body objects can re-create it if necessary
  if (Body::typicalInstance != nullptr)
  {
    Body* ti = Body::typicalInstance;
    Body::typicalInstance = nullptr;
    delete ti;
  }
}
