#include "Passenger.h"

/**
 * Passenger's constructor
 * @param source - the passenger's source point
 * @param destination - the passenger's destination point
 */
Passenger::Passenger(Node* source, Node* destination) {
    this->source = source;
    this->destination = destination;
}
/**
 * setRandomRate function
 * @return the passenger's rate for the ride
 */
int Passenger::setRandomRate() {
    return 1;
}
/**
 * Passenger's empty constructor
 */
Passenger::Passenger() {}
/**
 * Passenger dtor.
 */
Passenger::~Passenger() {
}
