#ifndef CLUSTER_H
#define CLUSTER_H

#include "galaxy.h"
#include "component.h"
#include "composite.h"

//Primitive Cluster Leaf class

using namespace std;

class Cluster: public Component
{
public:
    Cluster() {}
    Cluster( const Component& ) {}

    Cluster(string name, vector<Galaxy*> objects) :
        m_name(name),
        m_objects(objects) { }

    Cluster(string name, vector<Cluster*> clusters) :
        m_name(name),
        m_clusters(clusters) { }

    Cluster(string name,
            vector<Galaxy*> objects,
            vector<Cluster*> clusters) :
        m_name(name),
        m_objects(objects),
        m_clusters(clusters) { }

    ~Cluster() {}

    //overriden inherited methods
    int getSize() { return m_objects.size() + m_clusters.size(); }
    const string getName()  { return m_name; }
    void setName(string name) { m_name = name; }
    void Add(Component* object) { m_components.push_back(object); }
    vector<Galaxy*> getGalaxies() { return m_objects; }
    void setGalaxies(vector<Galaxy*> g) { m_objects = g; }
    vector<Galaxy*>  returnGalaxy()  { return m_objects; }
    vector<Cluster*>  returnClusters()   { return m_clusters; }
    vector<Component*>  returnObjects()  { return m_components; }

    //non inherited methods
    void setClusters(vector<Cluster*> c) { m_clusters = c; }

protected:
    int m_size;
    string m_name;
    Composite m_compObject;
    vector<Component*> m_components;
    vector<Galaxy*> m_objects; //galaxies
    vector<Cluster*> m_clusters;
};

#endif // CLUSTER_H
