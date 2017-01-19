#ifndef EX1_DRIVER_H
#define EX1_DRIVER_H
#include <string>
#include <deque>
#include "Cab.h"
#include "Point.h"
#include "GridBase.h"
#include "MartialStatus.h"
#include "TripInfo.h"
#include "GridTwoD.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Driver Class.
 */
class Driver{
private:
    int id;
    int age;
    MartialStat martialStatus;
    int experienceYears;
    float averageSatisfaction;
    Cab* taxiCab;
    int cabId;
    Node* location;
    TripInfo* trip;
    deque<Node*> path;
    int clientDescriptor;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize (Archive & ar, const unsigned int version) {
        ar & id;
        ar & age;
        ar & martialStatus;
        ar & experienceYears;
        ar & averageSatisfaction;
        ar & cabId;
        ar & taxiCab;
        ar & trip;
        ar & location;
    }

public:
    Driver(int id, int age, MartialStat martialStatus, int experienceYears, Cab* taxiCab);
    Driver(int id, int age, MartialStat martialStatus, int experienceYears, int cabId);
    Driver();
    Node* getLocation();
    void move();
    void setTaxiCab(Cab *taxiCab);
    void setLocation(Node *location);
    Cab *getTaxiCab() const;
    void setTrip(TripInfo *trip);
    TripInfo *getTrip() const;
    int getId() const;
    virtual ~Driver();
    int getCabID() const;
    void setPath(deque<Node*> path);
    void setClientDescriptor(int clientDescriptor);
    int getClientDescriptor();
};

#endif //EX1_DRIVER_H
