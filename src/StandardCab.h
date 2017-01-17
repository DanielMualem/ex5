#ifndef EX1_STANDARDCAB_H
#define EX1_STANDARDCAB_H
#include "Cab.h"
#include <iostream>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
/**
 * StandardCab Class.
 */
class StandardCab : public  Cab {
private:
    double tariff;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Cab>(*this);
        ar & tariff;
    }

public:
    StandardCab(int cabId, Manufacturer manufacturer, Color color);
    void move();
    StandardCab();
    virtual ~StandardCab();
    string toString() const;
};
#endif //EX1_STANDARDCAB_H