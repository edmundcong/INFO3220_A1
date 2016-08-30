#ifndef KEYVALUECONFIG_H
#define KEYVALUECONFIG_H

#include <iostream>
#include <regex>
#include <string>
#include <list>

#include "debug.h"
#include "config_section.h"

/*
 * Represents the simulation configuration file.
 * Provides methods for reading, editing, and writing the config.
 * This class follows the RAII principle.
 */
class Config
{

public:
  /*
   * Creates a new Config object by reading the config file at filepath.
   */
  Config(std::string filepath);

  /*
   * Returns a ConfigSection* by the given name,
   * or a nullptr if it doesn't exist.
   */
  ConfigSection* getSection(std::string name) const;

  /*
   * Returns a std::list<ConfigSection*> of all sections in the config.
   */
  std::list<ConfigSection*> getSections() const;

  virtual ~Config();

private:
  // A series of regexps used for parsing/matching
  static std::regex REGEX_SECTION;
  static std::regex REGEX_PAIR;
  static std::regex REGEX_COMMENT;

  std::string m_filepath;
  std::list<ConfigSection*> m_sections;

  // Parses one configuration file line,
  // instantiating the necesary data structures.
  void parseLine(std::string line);

};

#endif // KEYVALUECONFIG_H
