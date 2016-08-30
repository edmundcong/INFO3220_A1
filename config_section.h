#ifndef KEY_VALUE_CONFIG_SECTION_H
#define KEY_VALUE_CONFIG_SECTION_H

#include <string>
#include <list>

#include "debug.h"
#include "config_keyvalue.h"

/*
 * Represents one section in the configuration file.
 * Sections begin with a name enclosed in [].
 *   e.g.  [Planet Earth]
 * Each section contains a list of ConfigKeyValue objects,
 * storing (key, value) pairs.
 */
class ConfigSection
{

public:
  /*
   * Creates a new ConfigSection with the given name
   */
  ConfigSection(std::string name);

  /*
   * Config section name getters and setters.
   */
  std::string getName() const;
  void setName(std::string name);

  /*
   * Returns a std::list containing pointers to every ConfigKeyValue
   * object stored in this section.
   */
  std::list<ConfigKeyValue*> getPairs() const;

  /*
   * Adds a new (key, value) pair to this ConfigSection, with
   * the given key and value strings.
   */
  void addPair(std::string key, std::string value);

  /*
   * Returns a list of strings containing the keys of every (key,value) pair
   * within this ConfigSection.
   */
  std::list<std::string> getKeys() const;

  /*
   * Returns a pointer to a single ConfigKeyValue pair where the key
   * matches the name specified in the key argument.
   * Throws invalid arugment exception if key is not found in section.
   */
  ConfigKeyValue* getByKey(std::string key) const;

  virtual ~ConfigSection();

private:
  std::string m_name;
  std::list<ConfigKeyValue*> m_keyvals;

};

#endif // KEY_VALUE_CONFIG_SECTION_H
