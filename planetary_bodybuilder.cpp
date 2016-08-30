#include "planetary_bodybuilder.h"
#include <QString>
#define CONF_CONTAINER   ("container")
#define CONF_COL   ("colour")
#define CONF_RAD   ("radius")
#define CONF_MASS  ("mass")
#define CONF_X_POS ("pos_x")
#define CONF_Y_POS ("pos_y")
#define CONF_X_VEL ("vel_x")
#define CONF_Y_VEL ("vel_y")
#define CONF_LABEL ("label")
#define CONF_BLACKHOLE ("blackhole")
#define CONF_SUN ("sun")
//#define CONF_TYPE ("containerType")
//#define CONF_NAME ("containerName")

#define ERR_STR ("WARNING: No/invalid config value for key: ")
#define ERR_DEF ("         Using default value: ")

PlanetaryBodyBuilder::PlanetaryBodyBuilder()
{
    // Clone the Body prototype to use as our base
    m_newBody = Body::getTypicalInstance()->clone();
}


void PlanetaryBodyBuilder::buildBody(ConfigSection *cs)
{
    m_configSection = cs;
    ConfigKeyValue* kv;

    // Read properties from config

    // Set body name to be same as config section name
    m_newBody->setName(m_configSection->getName());

    //Container
    try
    {
        kv = m_configSection->getByKey(CONF_CONTAINER);
        m_newBody->setContainerValue(kv->getBoolValue());
    }
    catch (...)
    {
        configError(CONF_CONTAINER, m_newBody->getContainerValue() ? "true" : "false");
    }
    try
    {
        kv = m_configSection->getByKey(CONF_COL);
        m_newBody->setColour(kv->getValue());
    }
    catch (...)
    {
        configError(CONF_COL, m_newBody->getColour());
    }

    // Mass
    try
    {
        kv = m_configSection->getByKey(CONF_MASS);
        m_newBody->setMass(kv->getDoubleValue());
    }
    catch (...)
    {
        configError(CONF_MASS,
                    QString::number(m_newBody->getMass()).toStdString());
    }

    // Radius
    try
    {
        kv = m_configSection->getByKey(CONF_RAD);
        m_newBody->setRadius(kv->getDoubleValue());
    }
    catch (...)
    {
        configError(CONF_RAD,
                    QString::number(m_newBody->getRadius()).toStdString());
    }

    // Position vector
    try
    {
        kv = m_configSection->getByKey(CONF_X_POS);
        m_newBody->setXPosition(kv->getDoubleValue() * AU);
    }
    catch (...)
    {
        configError(CONF_X_POS,
                    QString::number(m_newBody->getXPosition()).toStdString());
    }

    try
    {
        kv = m_configSection->getByKey(CONF_Y_POS);
        m_newBody->setYPosition(kv->getDoubleValue() * AU);
    }
    catch (...)
    {
        configError(CONF_Y_POS,
                    QString::number(m_newBody->getYPosition()).toStdString());
    }

    // Velocity vector
    try
    {
        kv = m_configSection->getByKey(CONF_X_VEL);
        m_newBody->setXVelocity(kv->getDoubleValue());
    }
    catch (...)
    {
        configError(CONF_X_VEL,
                    QString::number(m_newBody->getXVelocity()).toStdString());
    }

    try
    {
        kv = m_configSection->getByKey(CONF_Y_VEL);
        m_newBody->setYVelocity(kv->getDoubleValue());
    }
    catch (...)
    {
        configError(CONF_Y_VEL,
                    QString::number(m_newBody->getYVelocity()).toStdString());
    }

    // Render name option
    try
    {
        kv = m_configSection->getByKey(CONF_LABEL);
        m_newBody->setRenderName(kv->getBoolValue());
    }
    catch (...)
    {
        configError(CONF_LABEL, m_newBody->getRenderName() ? "true" : "false");
    }
    // Render blackhole option
    try
    {
        kv = m_configSection->getByKey(CONF_BLACKHOLE);
        m_newBody->setBlackHole(kv->getBoolValue());
    }
    catch (...)
    {
        configError(CONF_BLACKHOLE, m_newBody->getBlackHoleValue() ? "true" : "false");
    }
    try
    {
        kv = m_configSection->getByKey(CONF_SUN);
        m_newBody->setSunValue(kv->getBoolValue());
    }
    catch (...)
    {
        configError(CONF_SUN, m_newBody->getSunValue() ? "true" : "false");
    }

}

Body* PlanetaryBodyBuilder::getBody() const
{
    return m_newBody;
}

void PlanetaryBodyBuilder::configError(std::string keyName, std::string def)
{
    std::cerr << ERR_STR << keyName;
    std::cerr << " in [" << m_configSection->getName() << "]" << std::endl;
    std::cerr << ERR_DEF << def << std::endl;
}
