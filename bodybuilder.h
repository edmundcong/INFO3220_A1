#ifndef BUILDER_H
#define BUILDER_H

#include "config_section.h"
#include "solarsystem.h"
#include "galaxy.h"
#include "cluster.h"

/*
 * An abstract Builder class from which conrete Body Builders should inherit.
 */
class BodyBuilder
{

public:
  // Builds a generic Body (abstract method)
  virtual void buildBody(ConfigSection* confSec) = 0;

};

#endif // BUILDER_H
