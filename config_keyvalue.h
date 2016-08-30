#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

#include <string>

#include "debug.h"

/*
 * Represents a (key,value) pair from the config file.
 * Each ConfigKeyValue pair is contained within a ConfigSection.
 */
class ConfigKeyValue
{

public:
  ConfigKeyValue(std::string key, std::string value)
    :m_key(key),
     m_value(value) { }

  // Key and value getters:
  // Keys and values are stored as strings, so these return std::string.
  std::string getKey() const;
  std::string getValue() const;

  // Key and value setters.
  // Keys and values are stored as strings, so these accept std::string.
  void setKey(std::string key);
  void setValue(std::string value);

  // Returns the stored value, converted to an int
  int getIntValue() const;

  // Returns the stored value, converted to a long
  long getLongValue() const;

  // Returns the stored value, converted to a double
  double getDoubleValue() const;

  // Returns the stored value, converted to a bool
  // Expects either "true" or "false".
  // Anything deemed invalid will become "false".
  bool getBoolValue() const;

  virtual ~ConfigKeyValue();

private:
  std::string m_key, m_value;

};

#endif // KEYVALUEPAIR_H
