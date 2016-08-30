#ifndef COMPOSITECOMPONENT_H
#define COMPOSITECOMPONENT_H

#include <component.h>
#include <galaxy.h>

/* Composite class used if a leaf needs to contain
   an instance of itself (i.e. Cluster) */

class Cluster;

using namespace std;

class Composite: public Component
{
public:
    Composite() {}

    Composite(vector<Cluster*> clusters) :
        m_clusters(clusters) {}

    //overriden inherited methods
    virtual int getSize(){ return m_clusters.size(); }
    const virtual string getName(){ return m_name; }
    void setName(string name) { m_name = name; }
    void Add(Component* object) { m_components.push_back(object); }
    virtual Composite* GetComposite() { return this; }
    vector<Galaxy*> returnGalaxy() { return m_objects; }
    vector<Cluster*> returnClusters() { return m_clusters; }
    vector<Component*> returnObjects() { return m_components; }

    //non-inherited methods
    Component* returnObject() { return m_components.back(); }

    ~Composite() {}

protected:
    string m_name;
    int m_size;
    vector<Component*> m_components; //other clusters
    vector<Galaxy*> m_objects; //galaxies
    vector<Cluster*> m_clusters;
};

#endif // COMPOSITECOMPONENT_H
