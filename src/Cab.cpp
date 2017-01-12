#include "Cab.h"

Cab::Cab() {}
/**
 * ctor
 * @param cabId - id
 * @param kmPassed  - km that the Cab passed.
 * @param manufacturer - of the Cab
 * @param color - of the Cab.
 * @return - Cab object.
 */
Cab::Cab(int cabId, Manufacturer manufacturer, Color color) {
    this->cabId = cabId;
    this->kmPassed = 0;
    this->manufacturer = manufacturer;
    this->color = color;
    this->hasDriver = false;
}

/**
 * getKmPassed method.
 * @return - kmPassed
 */
int Cab::getKmPassed() const {
    return this->kmPassed;
}
/**
 * setHasDriver method.
 * @param hasDriver - bool.
 */
void Cab::setHasDriver(bool hasDriver) {
    this->hasDriver = hasDriver;
}
/**
 * getCabType method.
 * @return  - the cab type.
 */
int Cab::getCabType() const {
    return this->cabType;
}
/**
 * getCabId function
 * @return the cab's id
 */
int Cab::getCabId() const {
    return cabId;
}
/**
 * Cab dtor.
 */
Cab::~Cab() {

}