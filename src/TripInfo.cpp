
#include "TripInfo.h"
#include "GridTwoD.h"

/**
 * TripInfo constructor
 * @param id - the trip's id
 * @param start - the start point of the trip
 * @param end - the end point of the trip
 * @param numOfPass - the number of passengers
 * @param tariff- the trip's tariff
 */
TripInfo::TripInfo(int id, Node* start, Node* end, int numOfPass, double tariff, double time) {
    this->id = id;
    this->start = start;
    this->end = end;
    this->numOfPass = numOfPass;
    this->tariff = tariff;
    this->metersPassed = 0;
    this->time = time;
}
/**
 * TripInfo empty constructor
 * @return
 */
TripInfo::TripInfo() {
}
/**
 * getStart function
 * @return the start point of the trip
 */
Node *TripInfo::getStart() const {
    return start;
}
/**
 * getEnd function
 * @return the end point of the trip
 */
Node* TripInfo::getEnd() const {
    return end;
}
/**
 * TripInfo dtor.
 */
TripInfo::~TripInfo() {
}
/**
 * getTime function
 * @return the trip's time
 */
double TripInfo::getTime() const{
    return this->time;
}
/**
 * setPath function
 * @param path - the path of the trip
 */
void TripInfo::setPath(deque<Node*> path) {
    TripInfo::path = path;
    this->map->setAllVisited(false);
}
/**
 * getPath function
 * @return the trip's path
 */
deque<Node*> TripInfo::getPath() {
    return this->path;
}
/**
 * setMap function
 * @param map - the board's map
 */
void TripInfo::setMap(GridTwoD *map) {
    TripInfo::map = map;
}
/**
 * getMap function
 * @return the board's map
 */
GridTwoD* TripInfo::getMap() const {
    return map;
}