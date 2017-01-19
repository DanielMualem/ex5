#include <sstream>
#include "LuxuryCab.h"

/**
 * LuxuryCab constructor
 * @param cabId - the cab's id
 * @param kmPassed - the km that the cab passed
 * @param manufacturer - the cab's manufacturer
 * @param color - the cab's color
 * @param tariff - the cab's tariff
 */
LuxuryCab::LuxuryCab(int cabId, Manufacturer manufacturer, Color color) :
        Cab(cabId, manufacturer, color) {
    this->tariff = 2;
    this->cabType = 2;
}
/**
 * move function
 * moves the cab
 */
void LuxuryCab::move() {
    this->kmPassed += 2;
}
/**
 * LuxuryCab empty constuctor
 */
LuxuryCab::LuxuryCab() {
    this->cabType = 2;
    this->kmPassed = 0;
}
/**
 * LuxuryCab dtor.
 */
LuxuryCab::~LuxuryCab() {

}