#ifndef GALAXY_H
#define GALAXY_H

#include "component.h"
#include "solarsystem.h"

//Primitive Galaxy Leaf Class

using namespace std;

class Cluster;

class Galaxy: public Component
{
public:
    Galaxy() {}

    Galaxy(string name,
           vector<solarSystem> sSystem) : //may contain solar systems and black holes
        m_name(name),
        m_sSystem(sSystem) { }

    Galaxy(string name,
           vector<Body*> blackHoles) : //may contain solar systems and black holes
        m_name(name),
        m_blackHoles(blackHoles) { }

    Galaxy(string name,
           vector<solarSystem> sSystem,
           vector<Body*> blackHoles) :
        m_name(name), m_sSystem(sSystem),
        m_blackHoles(blackHoles) { }

    ~Galaxy() {}

    //overriden inherited methods
    vector<Body*> containsObjects() { return m_blackHoles; }
    int getSize() { return ((int) m_blackHoles.size() + (int) m_sSystem.size()); }
    const string getName() { return m_name ;}
    void setName(string name) { m_name = name; }
    void Add(Component* object) { m_components.push_back(object); }

    vector<Galaxy*> returnGalaxy() { return m_objects; }
    vector<Cluster*>  returnClusters()   { return m_clusters; }
    vector<Component*>  returnObjects()  { return m_components; }

    //non-inherited methods
    void AddSolarSystem(solarSystem object) { m_sSystem.push_back(object); }
    void AddBlackHole(Body* blackHole) { m_blackHoles.push_back(blackHole); }
    vector<solarSystem> containsSolarSystems() { return m_sSystem; }

protected:
    string m_name;
    int m_size;
    vector<solarSystem> m_sSystem; //used to store objects in container
    vector<Body*> m_blackHoles;
    vector<Component*> m_components;
    vector<Cluster*> m_clusters;
    vector<Galaxy*> m_objects;
};

#endif // GALAXY_H
