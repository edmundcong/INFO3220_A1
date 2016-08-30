#ifndef CONTAINER_H
#define CONTAINER_H

#include "body.h"

#include <string>
#include <vector>
#include <list>

/* Component Abstract creational design pattern used.
   This is the component class which all leaf classes
   inherit from. */

class Composite;
class Galaxy;
class Cluster;

using namespace std;

class Component
{
public:
    Component() {} //default constructor
    ~Component() {}

    // Pure virtual functions (must be overriden)
    virtual int getSize() = 0;
    virtual void setName(string) = 0;
    virtual void Add(Component*) = 0; //composite add child function
    virtual vector<Galaxy*> returnGalaxy() = 0;
    virtual vector<Cluster*>  returnClusters()  = 0;
    virtual vector<Component*>  returnObjects() = 0;

    // Virtual functions (can be overriden)
    virtual const string getName() { return m_name; }
    virtual Composite* GetComposite() { return 0; }
    Component* getComponent() { return this; }

protected:
    int m_counter = 0;
    string m_name;
    vector<Component*> m_components;
    vector<Galaxy*> m_objects; //galaxies
    vector<Cluster*> m_clusters;
};

#endif // CONTAINER_H
