#ifndef EX1_PASSENGER_H
#define EX1_PASSENGER_H
#include "Point.h"
/**
 * Passanger Class.
 */
class Passenger {
private:
    Node* source;
    Node* destination;

public:
    Passenger();
    Passenger(Node* source, Node* destination);
    int setRandomRate();
    virtual ~Passenger();
};
#endif //EX1_PASSENGER_H
