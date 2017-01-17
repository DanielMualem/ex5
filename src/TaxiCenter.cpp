#include "TaxiCenter.h"
#include "BFS.h"

/**
 * TaxiCenter ctor.
 * @return - TaxiCenter object.
 */
TaxiCenter::TaxiCenter(GridTwoD* map) {
    this->time = 0;
    this->map = map;
}
/**
 * addDriver function
 * adds a driver to the drivers' vector
 * @param driver - the driver that needs to be added
 */
void TaxiCenter::addDriver(Driver* driver) {
    this->drivers.push_back(driver);
}
/**
 * addCab function
 * adds a cab to the cabs' vector
 * @param cab - the cab that needs to be added
 * */
void TaxiCenter::addCab(Cab* cab) {
    this->cabs.push_back(cab);
}
/**
 * addTrip function
 * adds a trip to the trips' vector
 * @param trip - the trip that reeds to be added
 */
void TaxiCenter::addTrip(TripInfo* trip) {
    this->trips.push_back(trip);
}
/**
 * getCab function
 * @param cabId - the id of the cab
 * @return the cab which has this id
 */
Cab* TaxiCenter::getCab(int cabId) {
    for (int i =0; i < (int)cabs.size(); i++) {
        if (cabs[i]->getCabId() == cabId) {
            return cabs[i];
        }
    }
    return NULL;
}
/**
 * getDriver function
 * @param driverId - the driver's id
 * @return the driver with that id
 */
Driver* TaxiCenter::getDriver(int driverId) {
    for (int i = 0; i < (int)drivers.size(); i++) {
        if (drivers[i]->getId() == driverId) {
            return drivers[i];
        }
    }
    return NULL;
}
/**
 * moveAll function
 * assign trips to drivers and moves all the the drivers to their end point.
 */
void TaxiCenter::moveAll() {

    this->time++;

    for (int i = 0; i < (int)drivers.size(); i++) {
        TripInfo* trip = this->drivers[i]->getTrip();
        if ((trip != NULL) && (this->time > trip->getTime())) {
            drivers[i]->move();
        } else if ((trip == NULL) && (!this->trips.empty())) {
            for (int j = 0; j < (int)this->trips.size(); j++) {
                if ((this->trips[j]->getTime() == this->time) &&
                    (this->drivers[i]->getLocation()->isEqual(this->trips[j]->getStart()))) {

                    drivers[i]->setTrip(this->trips[j]);
                    //Point *start = (Point *) this->trips[j]->getStart();
                    //Point *end = (Point *) this->trips[j]->getEnd();
                    //deque<Node*> path = this->map->getPath(start, end);
                    this->drivers[i]->setPath(this->trips[j]->getPath());
                    this->map->setAllVisited(false);
                    this->trips.erase(this->trips.begin() + j);
                }
            }
        }
    }
}
/**
 * TaxiCenter dtor.
 */
TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < (int)trips.size(); i++) {
        delete(trips[i]);
    }
    for (int i = 0; i < (int)cabs.size(); i++) {
        delete(cabs[i]);
    }
    for (int i = 0; i < (int)drivers.size(); i++) {
        delete(drivers[i]);
    }
}
/**
 * assign function
 * assinging a trip to each driver
 */
/*void TaxiCenter::assign() {
    for (int i = 0; i < (int)drivers.size(); i++) {
        if (drivers[i]->getTrip() == NULL) {
            drivers[i]->setTrip(this->trips[i]);
            Point *start = (Point *) this->trips[i]->getStart();
            Point *end = (Point *) this->trips[i]->getEnd();
            deque<Node *> path = this->map->getPath(start, end);
            this->drivers[i]->setPath(path);
        }
    }
}*/

void* TaxiCenter::computePathToTrip(void* element) {
    BFS bfs;
    TripInfo* trip = (TripInfo*)element;
    deque<Node*> path = bfs.shortestPathBFS(trip->getMap(), trip->getStart(), trip->getEnd());
    tr1ip->setPath(path);
    return NULL;
}