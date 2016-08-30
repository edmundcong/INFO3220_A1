#include "planetary_bodybuilder.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "component.h"
#include "galaxy.h"
#include "solarsystem.h"
#include "cluster.h"
#include <sstream>
#include <stdio.h>
#include <QGraphicsLineItem>


// time step for the simulation (default 10000)
#define TIMESTEP (10000)

// width and height of dialog box
#define DIALOG_WIDTH (1920)
#define DIALOG_HEIGHT (1080)

#define WARN_NO_GALAXY ("WARNING: NO SOLAR SYSTEM AND BLACKHOLES DEFINED FOR GALAXY: ")
#define WARN_NO_CLUSTER ("WARNING: NO GALAXIES AND CLUSTER DEFINED FOR CLUSTER: ")

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    // Read config file config.ini from the working dir
    try
    {
        m_config = new Config("config.ini");
    }
    catch (const std::invalid_argument&)
    {
        std::cerr << "No simulation config! Exiting..." << std::endl;
        exit(1);
    }

    // Build the bodies, solar systems, galaxies, clusters
    vector<Body*> planetVector;

    // Vectors used for Solar System object
    vector<solarSystem> tempSolarVector;
    vector<solarSystem> solarVector;

    // Vectors used for Galaxy object
    vector<Galaxy*> tempGalaxyVector;
    vector<Galaxy> galaxyVector;

    // Vectors used for cluster object
    vector<Cluster*> tempClusterVector;
    vector<Cluster> clusterVector;
    vector<Cluster> objClusterVect;
    vector<Cluster*> clustVector;
    Composite compositeObject;

    for (ConfigSection* cs : m_config->getSections())
    {
        try {
            // If the current object in the config file is a container
            if (cs->getByKey("container")->getBoolValue() == true) {

                string type = cs->getByKey("type")->getValue();
                string containerName = "";
                string containerString = "";
                string blackHoleString = "";
                string clusterString = "";
                string token = "";

                vector<string> containerStrings;

                // Check if the type is a solar system
                if (type  == "solarsystem") {
                    containerName = cs->getName();
                    containerString = cs->getByKey("contains")->getValue();
                    stringstream ss(containerString);
                    while(getline(ss, token, ',')){
                        containerStrings.push_back(token);
                        for (unsigned int i = 0; i < m_bodiesVector.size(); i++)
                        {
                            Body *tempBody = m_bodiesVector.at(i);
                            if (tempBody->getName() == token){
                                planetVector.push_back(tempBody);
                            }
                        }
                    }
                    solarVector.push_back(solarSystem(containerName, planetVector));
                    planetVector.clear();
                    containerStrings.clear();
                // Check if the type is a galaxy
                } else if (type == "galaxy") {
                    containerName = cs->getName();
                    try {
                        containerString = cs->getByKey("containsSystems")->getValue();
                    } catch (...) {}
                    try {
                        blackHoleString = cs->getByKey("containsBlackHoles")->getValue();
                    } catch (...) {}
                    if ((containerString == "") && (blackHoleString == ""))
                    {
                        cerr << WARN_NO_GALAXY << containerName << endl;
                        continue;
                    }
                    Galaxy galaxyObject;
                    galaxyObject.setName(containerName);
                    if (containerString != "")
                    {
                        stringstream ss(containerString);
                        solarSystem tempSolarSystem;
                        while (getline(ss, token, ',')){
                            for (unsigned int j = 0; j < solarVector.size(); j++)
                            {
                                tempSolarSystem = solarVector.at(j);
                                if (tempSolarSystem.getName() == token)
                                {
                                    galaxyObject.AddSolarSystem(tempSolarSystem);
                                }
                            }
                        }
                    }
                    if (blackHoleString != "")
                    {
                        stringstream bh(blackHoleString);
                        Body* tempBlackHole;
                        while(getline(bh, token, ',')){
                            for (unsigned int i = 0; i < m_bodiesVector.size(); i++)
                            {
                                tempBlackHole = m_bodiesVector.at(i);
                                if (tempBlackHole->getName() == token)
                                {
                                    galaxyObject.AddBlackHole(tempBlackHole);
                                }
                            }
                        }
                    }
                    galaxyVector.push_back(galaxyObject);
                    tempSolarVector.clear();
                    containerStrings.clear();
                // Check if the type is a cluster
                } else if (type == "cluster")
                {
                    containerName = cs->getName();
                    try
                    {
                        containerString = cs->getByKey("containsGalaxies")->getValue();
                    } catch (...)
                    {}
                    try
                    {
                        clusterString = cs->getByKey("containsClusters")->getValue();
                    }
                    catch (...)
                    {}
                    if ((containerString == "") && (clusterString == ""))
                    {
                        cerr << WARN_NO_CLUSTER << containerName << endl;
                        continue;
                    }

                    Cluster clusterObject;
                    Cluster *vectorClusterObject;
                    Cluster *tempClusterObject;
                    Galaxy *tempGalaxy;
                    objClusterVect.emplace_back(clusterObject);
                    objClusterVect.back().setName(containerName);

                    if (containerString != "")
                    {
                        stringstream gl(containerString);
                        while (getline(gl, token, ',')){
                            for (unsigned int j = 0; j < galaxyVector.size(); j++)
                            {
                                tempGalaxy = &galaxyVector.at(j);
                                if (tempGalaxy->getName() == token){
                                    tempGalaxyVector.push_back(tempGalaxy);
                                }
                            }
                        }
                        objClusterVect.back().setGalaxies(tempGalaxyVector);
                    }
                    if (clusterString != "")
                    {
                        stringstream cl(clusterString);
                        while (getline(cl, token, ',')){
                            for (unsigned int i = 0; i < clusterVector.size(); i++)
                            {
                                tempClusterObject = &clusterVector.at(i);
                                if (tempClusterObject->getName() == token)
                                {
                                    tempClusterVector.push_back(tempClusterObject);
                                }
                            }
                        }
                        objClusterVect.back().setClusters(tempClusterVector);
                    }

                    // Construct and push to the back the current cluster object
                    clusterVector.emplace_back(objClusterVect.back());

                    /* Use composite object's Add() function to create new leaf object
                       with current cluster object data */
                    compositeObject.Add(&objClusterVect.back());

                    // Create temp component of current composite object
                    Component *tempComponent = compositeObject.returnObject();

                    // Make sure out cluster has either a galaxy or another cluster in it (or both)
                    if ((tempComponent->returnClusters().size() > 0 ) && (tempComponent->returnGalaxy().size() > 0))
                    {
                        vectorClusterObject = new Cluster(tempComponent->getName(),
                                                          tempComponent->returnGalaxy(),
                                                          tempComponent->returnClusters());
                        clustVector.emplace_back(vectorClusterObject);
                    }
                    else if (tempComponent->returnGalaxy().empty())
                    {
                        vectorClusterObject = new Cluster(tempComponent->getName(), tempComponent->returnClusters());
                        clustVector.emplace_back(vectorClusterObject);
                    }
                    else if (tempComponent->returnClusters().empty())
                    {
                        vectorClusterObject = new Cluster(tempComponent->getName(), tempComponent->returnGalaxy());
                        clustVector.emplace_back(vectorClusterObject);
                    }
                }
                tempGalaxyVector.clear();
                tempClusterVector.clear();
            }
        } catch (std::invalid_argument) {
            PlanetaryBodyBuilder builder;
            builder.buildBody(cs);
            Body *tempBody = builder.getBody();
            m_bodiesVector.push_back(tempBody);
            m_bodies.push_back(tempBody);
        }
    }
    // Create the dialog
    ui->setupUi(this);
    this->update();
    this->resize(DIALOG_WIDTH, DIALOG_HEIGHT);

    // Use a black background because it's SPAAAAAAAAAAAAAAACE
    this->setStyleSheet("background-color: #000000;");

    // Simulation is initially not paused
    this->paused = false;

    // Update the velocities and positions, etc. every 16ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(16);

    //String for outputting the tree of objects (clusters, galaxies, solarsystems)
    string returnStructure = this->getStructure(clustVector, galaxyVector, solarVector);

    QString qtStructure = QString::fromStdString(returnStructure);
    //calling method to concatinate string for label setting
    ui->label->setText(qtStructure);
}

void Dialog::nextFrame()
{
    if (this->paused) {
        return;
    }

    // Update total forces for all bodies b1, b2 where b1 != b2
    for (Body* b1 : m_bodies)
    {
        // Initial zero force vector for b1
        double xForce = 0.0,
                yForce = 0.0;

        // Add attraction between b1 and every other body
        for (Body* b2 : m_bodies)
        {
            if (b1 != b2)
            {
                b1->addAttraction(*b2, xForce, yForce);
            }
        }

        // Update b1 with the new force vector for the current timestep
        b1->update(xForce, yForce, TIMESTEP);
    }
    update();
}

Dialog::~Dialog()
{
    DEBUG("Dialog destructor");

    delete ui;
    delete m_config;

    // Ensure every body destructor is called when the Dialog is closed
    for (Body* b : m_bodies)
    {
        delete b;
    }
    m_bodies.clear();
}

// location of center
#define X_CENTER (300)
#define Y_CENTER (300)

// offset for text rendering
#define TXT_X_OFFSET (-35)
#define TXT_Y_OFFSET (+15)

// scaling constant for rendering bodies on screen
// (zoomed out a bit compared to tutorial code)
#define SCALE (160 / AU)

void Dialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // set pen
    QPen bodyPen(Qt::black);
    bodyPen.setWidth(1);

    // White brush for text
    QPen textPen(Qt::white);
    textPen.setWidth(1);

    // paint all bodies
    for (Body* b : m_bodies)
    {
        // If black hole label set custom values
        if (b->getBlackHoleValue() == true){
            b->setMass(1.98892e30);
            QColor colour(54, 48, 74);
            QBrush brush(colour);
            painter.setBrush(brush);
            painter.setPen(bodyPen);
        } else {
            // If sun draw zodiac with the sun and all
            // other sun objects
            if ((b->getSunValue() == true) &&
                    (Dialog::getZodiac() == true)){
                painter.setPen(QPen(Qt::white));
                int xA = X_CENTER - b->getXPosition() * SCALE;
                int yA = Y_CENTER - b->getYPosition() * SCALE;
                for (Body* currentBody : m_bodies){
                    if (currentBody->getSunValue() == true){
                        int xB = X_CENTER - currentBody->getXPosition() * SCALE;
                        int yB = Y_CENTER - currentBody->getYPosition() * SCALE;
                        painter.drawLine(xA, yA, xB, yB);
                    }
                }

            }

            // Create a QColour and brush from the hexadecimal colour code
            QColor colour(b->getColour().c_str());
            QBrush brush(colour);
            painter.setBrush(brush);
            painter.setPen(bodyPen);
        }

        // use a QPointF and radius so the body is centered correctly
        painter.drawEllipse(QPointF(X_CENTER - b->getXPosition() * SCALE,
                                    Y_CENTER - b->getYPosition() * SCALE),
                            b->getRadius(), b->getRadius());

        // paint the name of the body (extension for assign 1)
        if (b->getRenderName())
        {
            painter.setPen(textPen);
            painter.drawText(
                        QPointF(X_CENTER - b->getXPosition() * SCALE + TXT_X_OFFSET,
                                Y_CENTER - b->getYPosition() * SCALE + b->getRadius() + TXT_Y_OFFSET),
                        b->getName().c_str());
        }
    }
}

// Key press event for pausing the simulation
void Dialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        Dialog::paused = !this->paused;
    }
}

// Method to append the object structure to a string so it can then be inserted into a label
string Dialog::getStructure(vector<Cluster*> clusterVect, vector<Galaxy> galaxyVect,
                            vector<solarSystem> solarVect)
{
    // Variables and data containers needed for this method
    string returnStructure = "";
    vector<Galaxy*> galaxyVector;
    vector<solarSystem> tempSolarVector;
    vector<Body*> planetVector;

    /* If a cluster exists then it will loop through every single one
       appending to the string the cluster, it's galaxies/galaxy/black holes,
       their solar systems, and then their objects.*/
    if (clusterVect.size() > 0){
        for (unsigned int i = 0; i < clusterVect.size(); i++)
        {
            Cluster *temp = clusterVect.at(i);
            returnStructure.append("[Cluster Name: " + temp->getName() + "]" + "\n");
            galaxyVector = temp->getGalaxies();
            for (unsigned int i = 0; i < galaxyVector.size(); i++)
            {
                Galaxy* gtemp = galaxyVector.at(i);
                returnStructure.append("|-->Galaxy Name: " + gtemp ->getName() + "\n");
                tempSolarVector = gtemp->containsSolarSystems();
                for (unsigned int j = 0; j < tempSolarVector.size(); j++)
                {
                    solarSystem tempSolarSystem = tempSolarVector.at(j);
                    planetVector = tempSolarSystem.containsObjects();
                    returnStructure.append("|---->Solar System Name: " + tempSolarSystem.getName() + "\n");
                    for (unsigned int k = 0; k < planetVector.size(); k++)
                    {
                        Body* tempBody = planetVector.at(k);
                        returnStructure.append("|-------->Planet Name: " + tempBody->getName() + "\n");
                    }
                }
                planetVector = gtemp->containsObjects();
                for (unsigned int j = 0; j < planetVector.size(); j++)
                {
                    try {
                        Body* tempBody = planetVector.at(j);
                        returnStructure.append("|---->Blackhole Name: " + tempBody->getName() + "\n");
                    } catch ( ... ) { }
                }
            }
            returnStructure.append("\n");
        }
    }
    // Similar to the above loop except starts from the galaxies incase no clusters are found
    else if (galaxyVect.size() > 0)
    {
        for (unsigned int i = 0; i < galaxyVect.size(); i++)
        {
            Galaxy gtemp = galaxyVect.at(i);
            returnStructure.append("|-->Galaxy Name: " + gtemp.getName() + "\n");
            tempSolarVector = gtemp.containsSolarSystems();
            for (unsigned int j = 0; j < tempSolarVector.size(); j++)
            {
                solarSystem tempSolarSystem = tempSolarVector.at(j);
                planetVector = tempSolarSystem.containsObjects();
                returnStructure.append("|---->Solar System Name: " + tempSolarSystem.getName() + "\n");
                for (unsigned int k = 0; k < planetVector.size(); k++)
                {
                    Body* tempBody = planetVector.at(k);
                    returnStructure.append("|-------->Planet Name: " + tempBody->getName() + "\n");
                }
            }
            planetVector = gtemp.containsObjects();
            for (unsigned int j = 0; j < planetVector.size(); j++)
            {
                try {
                    Body* tempBody = planetVector.at(j);
                    returnStructure.append("|---->Blackhole Name: " + tempBody->getName() + "\n");
                } catch ( ... ) { }
            }
            returnStructure.append("\n");
        }
    }
    // Similar to the above loop except starts from the solar systems incase no galaxies are found
    else if (solarVect.size() > 0)
    {
        for (unsigned int j = 0; j < solarVect.size(); j++)
        {
            solarSystem tempSolarSystem = solarVect.at(j);
            planetVector = tempSolarSystem.containsObjects();
            returnStructure.append("|---->Solar System Name: " + tempSolarSystem.getName() + "\n");
            for (unsigned int k = 0; k < planetVector.size(); k++)
            {
                Body* tempBody = planetVector.at(k);
                returnStructure.append("|-------->Planet Name: " + tempBody->getName() + "\n");
            }
        }
        returnStructure.append("\n");
    }
    return returnStructure;
}


/* Method to set the zodiac member variable and therefore
   trigger the Zodiac functionality */
void Dialog::on_pushButton_clicked()
{
    bool temp = Dialog::getZodiac();
    if (temp == true)
    {
        temp = false;
    } else
    {
        temp = true;
    }
    Dialog::setZodiac(temp);
}

/* Needed to implement a button since the space-bar triggering of the 'pause' was
   instead triggering the Zodiac button since it was automatically highlighted*/
void Dialog::on_pushButton_2_clicked()
{
    Dialog::paused = !this->paused;
}
