#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "component.h"

//Primitive Solar System Leaf Class

using namespace std;

class Galaxy;
class Cluster;

class solarSystem : public Component
{
public:
    solarSystem() {}

    solarSystem(string name,
              vector<Body*> objects) :  //may contain sun and planets
        m_name(name),
        m_objects(objects) { }
        //Component(name, objects) { }

    ~solarSystem() {}

    //overriden inherited methods
    vector<Body*> containsObjects() { return m_objects; }
    int getSize() { return m_objects.size(); }
    const string getName() { return m_name ;}
    void setName(string name) { m_name = name; }
    void Add(Component* object) { m_components.push_back(object); }
    vector<Galaxy*> returnGalaxy() { return m_galaxies; }
    vector<Cluster*>  returnClusters()   { return m_clusters; }
    vector<Component*>  returnObjects()  { return m_components; }

protected:
    string m_name;
    int m_size;
    vector<Body*> m_objects;
    vector<Component*> m_components;
    vector<Galaxy*> m_galaxies;
    vector<Cluster*> m_clusters;
};

#endif // SOLARSYSTEM_H
