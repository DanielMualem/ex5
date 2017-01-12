#ifndef EX1_TRIPINFO_H
#define EX1_TRIPINFO_H

#include "Point.h"
#include <boost/serialization/base_object.hpp>

/**
 * TripInfo Class.
 */
using namespace std;

class TripInfo {
private:
    int id;
    int metersPassed;
    Node* start;
    Node* end;
    int numOfPass;
    double tariff;
    double time;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize (Archive & ar, const unsigned int version) {
        ar & id;
        ar & metersPassed;
        ar & start;
        ar & end;
        ar & numOfPass;
        ar & tariff;
        ar & time;
    }

public:
    TripInfo(int id, Node* start, Node* end, int numOfPass, double tariff, double time);
    TripInfo();
    Node *getStart() const;
    Node *getEnd() const;
    virtual ~TripInfo();
    double getTime() const;
};

#endif //EX1_TRIPINFO_H