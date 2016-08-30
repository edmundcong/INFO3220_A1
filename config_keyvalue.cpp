#include <algorithm>
#include <QString>
#include <stdexcept>

#include "config_keyvalue.h"

std::string ConfigKeyValue::getKey() const
{
  return m_key;
}

std::string ConfigKeyValue::getValue() const
{
  return m_value;
}

int ConfigKeyValue::getIntValue() const
{
  bool ok;
  int num = QString::fromStdString(m_value).toInt(&ok);
  if(!ok)
      throw std::invalid_argument("Conversion Error");
  return num;
}

long ConfigKeyValue::getLongValue() const
{
    bool ok;
    long num = QString::fromStdString(m_value).toLong(&ok);
    if(!ok)
        throw std::invalid_argument("Conversion Error");
    return num;
}

double ConfigKeyValue::getDoubleValue() const
{
    bool ok;
    double num = QString::fromStdString(m_value).toDouble(&ok);
    if(!ok)
        throw std::invalid_argument("Conversion Error");
    return num;
}

bool ConfigKeyValue::getBoolValue() const
{
  std::string val(m_value);
  std::transform(val.begin(), val.end(), val.begin(), ::tolower);
  return m_value == "true";
}

void ConfigKeyValue::setKey(std::string key)
{
  m_key = key;
}

void ConfigKeyValue::setValue(std::string value)
{
  m_value = value;
}

ConfigKeyValue::~ConfigKeyValue()
{
  DEBUG("KVP destructor");
}
