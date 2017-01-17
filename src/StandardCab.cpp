#include "StandardCab.h"
#include <boost/serialization/access.hpp>
#include <sstream>
/**
 * StandardCab's constructor
 * @param cabId - the cab's id
 * @param kmPassed - the km that the cab passed
 * @param manufacturer -  the cab's manufacturer
 * @param color - the cab's color
 * @param tariff - the cab's tariff
 */
StandardCab::StandardCab(int cabId, Manufacturer manufacturer, Color color) :
        Cab(cabId, manufacturer, color) {
    this->tariff = 1;
    this->cabType = 1;
}
/**
 * move function
 * moves the cab
 */
void StandardCab::move() {
    this->kmPassed++;
}
/**
 * StandardCab's empty constructor
 */
StandardCab::StandardCab() {
    this->cabType = 1;
    this->kmPassed = 0;
}
/**
 * StandardCab dtor.
 */
StandardCab::~StandardCab() {

}
string StandardCab::toString() const{

    stringstream sx;
    sx << this->cabId;
    string cabId = sx.str();
    stringstream sy;
    sy << this->tariff;
    string tariff = sy.str();

    return "the cab's id is: " + cabId +  " the tariff is: " + tariff;
}
//BOOST_CLASS_EXPORT(StandardCab)