#ifndef EX1_CAB_H
#define EX1_CAB_H
#include <string>
#include "Manufacturer.h"
#include "Color.h"
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>

using namespace std;
/**
 * Cab Class.
 */
class Cab {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & cabId;
        ar & kmPassed;
        ar & manufacturer;
        ar & color;
        ar & hasDriver;
        ar & cabType;
    }
protected:
    int cabId;
    int kmPassed;
    Manufacturer manufacturer;
    Color color;
    bool hasDriver;
    int cabType;

public:
    Cab(int cabId, Manufacturer manufacturer, Color color);
    Cab();
    virtual void move() = 0;
    int getKmPassed() const;
    void setHasDriver(bool hasDriver);
    int getCabType() const;
    int getCabId() const;
    virtual ~Cab();
};
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab);

#endif //EX1_CAB_H
