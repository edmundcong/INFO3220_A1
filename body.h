#ifndef BODY_H
#define BODY_H

#include <string>
#include <vector>

#include "prototype.h"

// gravitational constant
#define G (6.67428e-11)

// astronomical unit
#define AU (1.4960000e+11)

class Body : public Prototype
{

private:
  //container flag
  bool m_container;

//  std::string m_containerType;
//  std::string m_containerName;
//  std::vector<std::string> m_contains;

  // mass of body
  double m_mass;

  // radius of body in simulation
  double m_radius;

  // position vector of body
  double m_xPosition;
  double m_yPosition;

  // velocity vector of body
  double m_xVelocity;
  double m_yVelocity;

  // name of body in simulation
  std::string m_name;

  // colour of body in simulation
  std::string m_colour;

  // whether or not the name is rendered (default = true)
  bool m_renderName;

  //whether or not the object is a blackhole (default = false)
  bool m_blackHole;

  //whether or not the object is a sun (default = false)
  bool m_sun;

  // prototypical Body instance
  static Body* typicalInstance;

public:
  Body(bool container = false,
//       std::string containerType = "",
//       std::string containerName = "",
       double mass = 0.0,
       double radius = 0.0,
       double xPosition = 0.0,
       double yPosition = 0.0,
       double xVelocity = 0.0,
       double yVelocity = 0.0,
       std::string colour = "#FFFFFF",
       std::string name = "Body",
       bool renderName = true,
       bool blackHole = false,
       bool sun = false) :
    m_container(container),
//    m_containerType(containerType),
//    m_containerName(containerName),
//    m_contains(contains),
    m_mass(mass),
    m_radius(radius),
    m_xPosition(xPosition),
    m_yPosition(yPosition),
    m_xVelocity(xVelocity),
    m_yVelocity(yVelocity),
    m_name(name),
    m_colour(colour),
    m_renderName(renderName),
    m_blackHole(blackHole),
    m_sun(sun)  { }

  virtual ~Body();

  Body* clone();

  static Body* getTypicalInstance();

  // get body name
  std::string getName() const { return m_name; }

  // get body colour
  std::string getColour() const { return m_colour; }

  // get body mass
  double getMass() const { return m_mass; }

  // get position of body
  double getXPosition() const { return m_xPosition; }
  double getYPosition() const { return m_yPosition; }

  // get velocity of body
  double getXVelocity() const { return m_xVelocity; }
  double getYVelocity() const { return m_yVelocity; }

  // get Euclidean distance to other body
  double getDistance(const Body &other) const;

  // set body name
  void setName(std::string name) { m_name = name; }

  // set body colour
  void setColour(std::string colour) { m_colour = colour; }

  // set body mass
  void setMass(double mass) { m_mass = mass; }

  // set position of body
  void setXPosition(double xpos) { m_xPosition = xpos; }
  void setYPosition(double ypos) { m_yPosition = ypos; }

  // set velocity of body
  void setXVelocity(double xvel) { m_xVelocity = xvel; }
  void setYVelocity(double yvel) { m_yVelocity = yvel; }

  // add exerted force vector from body "other"
  void addAttraction(const Body &other, double &xForce, double &yForce);

  // update velocity and position by total force for one time step
  void update(double xTotalForce, double yTotalForce, double timestep);

  // get radius for simulation
  double getRadius() const { return m_radius; }

  // set radius for simulation
  void setRadius(double radius) { m_radius = radius; }

  // getter and setter for renderName option
  // this specifies whether the body's name will be rendered in the simulation
  bool getRenderName() const;
  void setRenderName(bool renderName);

  // getter and setter for whether or not an object is a black hole
  bool getBlackHoleValue() const;
  void setBlackHole(bool blackHole);

  // getter and setter for whether or not an "object" can contain others
  bool getContainerValue() const;
  void setContainerValue(bool container);

  // getter and setter for whether or not an object is a sun
  bool getSunValue() const;
  void setSunValue(bool sun);
};

#endif // BODY_H
