#ifndef EX1_TAXICENTER_H
#define EX1_TAXICENTER_H
#include "Cab.h"
#include "Driver.h"
#include "TripInfo.h"
#include <deque>

/**
 * TaxiCenter Class.
 */
class TaxiCenter{
private:
    vector<Driver*> drivers;
    vector<Cab*> cabs;
    vector<TripInfo*> trips;
    double time;
    GridTwoD* map;

public:
    TaxiCenter(GridTwoD* map);
    void addDriver(Driver* driver);
    void addCab(Cab* cab);
    void addTrip(TripInfo* trip);
    Cab* getCab(int cabId);
    Driver* getDriver(int driverId);
    void moveAll();
    virtual ~TaxiCenter();
    void assign();
};
#endif //EX1_TAXICENTER_H
