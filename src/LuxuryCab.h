#ifndef EX1_LUXURYCAB_H
#define EX1_LUXURYCAB_H
#include "Cab.h"
#include <iostream>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>

/**
 * LuxuryCab Class.
 */
class LuxuryCab : public Cab {
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
    LuxuryCab(int cabId, Manufacturer manufacturer, Color color);
    void move();
    virtual ~LuxuryCab();
    LuxuryCab();
    string toString() const;
};
#endif //EX1_LUXURYCAB_H
