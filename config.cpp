#include <fstream>
#include <regex>
#include <stdexcept>

#include "config.h"

#define REGEX_CONF_SECTION ("^\\s*\\[([^\\]]+)\\]\\s*$")
#define REGEX_CONF_KVPAIR  ("^\\s*([^=]+?)\\s*=\\s*(.+?)\\s*$")
#define REGEX_CONF_COMMENT ("(^\\s*;.*$)|(^\\s*$)")

#define ERR_INVALID_CONF_LINE ("ERROR: Invalid config line (ignoring): ")
#define ERR_OPEN              ("ERROR: Failed to open config file: ")

#define WARN_NOBODY           ("WARNING: No bodies defined in config file: ")

std::regex Config::REGEX_SECTION(REGEX_CONF_SECTION);
std::regex Config::REGEX_PAIR(REGEX_CONF_KVPAIR);
std::regex Config::REGEX_COMMENT(REGEX_CONF_COMMENT);

Config::Config(std::string filepath)
  :m_filepath(filepath)
{
  // Read the config file line-by-line using std::getline
  std::ifstream configFile(m_filepath.c_str());

  // Couldn't open. Print to stderr and throw an exception.
  if (!configFile)
  {
    std::cerr << ERR_OPEN << m_filepath << std::endl;
    throw std::invalid_argument("Failed to open given config file: " +
                                m_filepath);
  }

  // Read line-by-line
  std::string line;
  while (std::getline(configFile, line))
  {
    // Parse every config file line and build the config object
    parseLine(line);
  }

  if (configFile.is_open())
  {
    configFile.close();
  }

  if (m_sections.size() == 0)
  {
    std::cerr << WARN_NOBODY << m_filepath << std::endl;
  }
}

ConfigSection* Config::getSection(std::string name) const
{
  for (ConfigSection* s : m_sections)
  {
    if (s->getName() == name)
    {
      return s;
    }
  }

  // Section not found, return NULL
  return nullptr;
}

std::list<ConfigSection*> Config::getSections() const
{
  return m_sections;
}

void Config::parseLine(std::string line)
{
  // regex match object for capturing group matches
  std::smatch sm;

  // Process comment/blank lines
  if (std::regex_match(line, Config::REGEX_COMMENT))
  {
      return; // the line is a comment or blank - nothing to do
  }

  // Process section names
  else if (std::regex_match(line, sm, Config::REGEX_SECTION) && sm.size() > 1)
  {
    m_sections.emplace_back(new ConfigSection(sm[1]));
  }

  // Process section key-value pairs
  else if (std::regex_match(line, sm, Config::REGEX_PAIR) && sm.size() > 2)
  {
    ((ConfigSection*) m_sections.back())->addPair(sm[1], sm[2]);
  }

  // Any line which isn't matched should be considered invalid
  else
  {
    // Print invalid line error message to stderr
    std::cerr << ERR_INVALID_CONF_LINE;
    std::cerr << line << std::endl;
  }
}

Config::~Config()
{
  DEBUG("Config destructor");

  for (ConfigSection* section : m_sections)
  {
    delete section;
  }

  m_sections.clear();
}
