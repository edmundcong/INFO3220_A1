#include <stdexcept>

#include "config_section.h"

ConfigSection::ConfigSection(std::string name)
  :m_name(name)
{ }

std::string ConfigSection::getName() const
{
  return m_name;
}

void ConfigSection::setName(std::string name)
{
  m_name = name;
}

void ConfigSection::addPair(std::string key, std::string value)
{
  m_keyvals.push_back(new ConfigKeyValue(key, value));
}

std::list<ConfigKeyValue*> ConfigSection::getPairs() const
{
  return m_keyvals;
}

ConfigKeyValue* ConfigSection::getByKey(std::string key) const
{
  for (ConfigKeyValue* kv : m_keyvals)
  {
    if (kv->getKey() == key)
    {
      return kv;
    }
  }

  // Not found, throw invalid arg exception
  throw std::invalid_argument("Key not found: " + key);
}

ConfigSection::~ConfigSection()
{
  DEBUG("CS destructor");

  for (ConfigKeyValue* kv : m_keyvals)
  {
    delete kv;
  }

  m_keyvals.clear();
}
