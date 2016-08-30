#ifndef PLANETARYBODYBUILDER_H
#define PLANETARYBODYBUILDER_H

#include "body.h"
#include "bodybuilder.h"
#include "config_section.h"

/*
 * Builds a new planetary Body object.
 */
class PlanetaryBodyBuilder : public BodyBuilder
{

public:
  PlanetaryBodyBuilder();

  /*
   * Builds a new Planetary Body object from the values contained
   * within the provided ConfigSection.
   */
  void buildBody(ConfigSection *cs);

  /*
   * Returns a pointer to the built Body object.
   */
  Body* getBody() const;

  /*
   * DESTRUCTOR NOTE: newly created Body is **NOT** deleted here.
   * The user must delete it with the pointer returned by getBody().
   */
  virtual ~PlanetaryBodyBuilder() { }

private:
  Body* m_newBody;
  ConfigSection* m_configSection;

  // Prints to stderr that keyName wasn't set properly, and
  // the value that will be used instead (from the prototype).
  // Error handling, yay!
  void configError(std::string keyName, std::string def);

};

#endif // PLANETARYBODYBUILDER_H
