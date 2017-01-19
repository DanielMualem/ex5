#include <sstream>
#include "Driver.h"
/**
 * Driver constructor
 * @param id - the driver's id
 * @param age - the driver's age
 * @param martialStatus - the driver's matiral status
 * @param experienceYears - the driver's years experience
 * @param taxiCab- the driver's cab
 */
using namespace std;

Driver::Driver(int id, int age, MartialStat martialStatus, int experienceYears, Cab* taxiCab) {
    this->id = id;
    this->age = age;
    this->martialStatus = martialStatus;
    this->experienceYears = experienceYears;
    this->averageSatisfaction = 0;
    this->cabId = taxiCab->getCabId();
    this->taxiCab = taxiCab;
    this->trip = NULL;
    this->location = new Point(0,0);
    //this->path = NULL;
}
/**
 * Driver constructor
 * @param id - the driver's id
 * @param age - the driver's age
 * @param martialStatus - the driver's matiral status
 * @param experienceYears - the driver's years experience
 * @param cabId- the driver's cab id
 */
Driver::Driver(int id, int age, MartialStat martialStatus, int experienceYears, int cabId){
    this->id = id;
    this->age = age;
    this->martialStatus = martialStatus;
    this->experienceYears = experienceYears;
    this->averageSatisfaction = 0;
    this->cabId = cabId;
    this->taxiCab = NULL;
    this->trip = NULL;
    this->location = new Point(0,0);
    //this->path = NULL;
}

/**
 * Driver's empty comstructor
 * initializes the loaction and the cab to null
 */
Driver::Driver() {
}

/**
 * setLocation function
 * sets the driver's location
 * @param location - the driver's location
 */
void Driver::setLocation(Node *location) {
    Point* tripLoc = (Point*)location;
    Point* driverLoc = (Point*)this->location;
    driverLoc->setX(tripLoc->getX());
    driverLoc->setY(tripLoc->getY());
}

/**
 * getLocation function
 * @return the driver's location
 */
Node* Driver::getLocation() {
    return this->location;
}
/**
 * setTaxiCab function
 * sets the driver's cab
 * @param taxiCab - the driver's cab
 */
void Driver::setTaxiCab(Cab *taxiCab) {
    this->taxiCab = taxiCab;
    this->taxiCab->setHasDriver(true);
}
/**
 * move function
 * moves the taxi
 */
void Driver::move() {
    if (!this->path.empty()) {
        Node* nextLoc;
        if ((this->taxiCab->getCabType() == 1) || (this->path.size() == 1)) {
            nextLoc = this->path.front();
            this->path.pop_front();
        } else {
            this->path.pop_front();
            nextLoc = this->path.front();
            this->path.pop_front();
        }

        this->setLocation(nextLoc);
        this->taxiCab->move();
    }

    if (this->location->isEqual(this->trip->getEnd())) {
        delete trip;
        this->trip = NULL;
    }
}

/**
 * getTaxiCab function
 * @return the driver's cab
 */
Cab *Driver::getTaxiCab() const {
    return this->taxiCab;
}
/**
 * setTrip function
 * sets a trip to the driver
 */
void Driver::setTrip(TripInfo *trip) {
    this->trip = trip;
}
/**
 * getTrip method.
 * @return - TripInfo of the Driver.
 */
TripInfo *Driver::getTrip() const {
    return trip;
}
/**
 * getId function
 * @return the driver's id
 */
int Driver::getId() const {
    return id;
}
/**
 * Driver dtor.
 */
Driver::~Driver() {
    delete location;

    if (trip != NULL) {
        delete trip;
    }
}
/**
 * setPath function
 * @param path - the trip's path
 */
void Driver::setPath(deque<Node*> path){
    this->path = path;
    this->path.pop_front();
}
/**
 * getCabID function
 * @return the cab's id
 */
int Driver::getCabID() const {
    return cabId;
}
/**
 * setClientDescriptor function
 * @param clientDescriptor- the client's socket's descriptor
 */
void Driver::setClientDescriptor(int clientDescriptor){
    this->clientDescriptor = clientDescriptor;
}
/**
 * getClientDescriptor function
 * @return clientDescriptor- the driver's socket's descriptor
 */
int Driver::getClientDescriptor(){
    return this->clientDescriptor;
}