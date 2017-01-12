#include <iostream>
#include "Point.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
/**
 * Point Constructor.
 * @param x - x.
 * @param y - y.
 */
Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
    this->isVisited = false;
    this->obstacle = false;
}
/**
 * Point default constructor.
 */
Point::Point() {
}
/**
 * func name: getNode.
 */
Node* Point::getNode() {
    return this;
}
/**
 * func name: getX.
 * @return - x of Point.
 */
int Point::getX() const {
    return this->x;
}
/**
 * func name: getY.
 * @return - y of Point.
 */
int Point::getY() const {
    return this->y;
}
/**
 * func name: isEqual.
 * @param node - node to compare with.
 * @return - true or false.
 */
bool Point::isEqual(Node* node) {

    Point* p = (Point*)node->getNode();
    return (this->x == p->getX()) && (this->y == p->getY());
}
/**
 * func name: setVisited.
 * @param isVisited - true or false.
 */
void Point::setVisited(bool isVisited) {
    this->isVisited = isVisited;
}
/**
 * func name: getIsVisited.
 * @return - isVisited value.
 */
bool Point::getIsVisited() const {
    return isVisited;
}
/**
 * func name: getDad.
 * @return - dad node.
 */
Node *Point::getDad() const {
    return dad;
}
/**
 * func name: setDad.
 * @param dad - dad node.
 */
void Point::setDad(Node *dad) {
    Point::dad = dad;
}
/**
 * func name: toString.
 * @return - string of Point like the following: (x,y).
 */
string Point::toString() const {

    stringstream sx;
    sx << this->x;
    string x = sx.str();
    stringstream sy;
    sy << this->y;
    string y = sy.str();

    return "(" + x + "," + y + ")";
}
/**
 * Point distructor.
 */
Point::~Point() {
}

const Point Point::operator+(const Point& point) const {
    return Point(this->x + point.getX(), this->y + point.getY());
}
/**
 * operator "==" overloading
 * @param point - the point's address
 * @return - true- if the points are eaual, false- if not
 */
bool Point::operator==(const Point& point) const {
    return (this->x == point.getX() && this->y == point.getY());
}
/**
 * operator "!=" overloading
 * @param point - the point's address
 * @return - false- if the points are eaual, true- if not
 */
bool Point::operator!=(const Point& point) const {
    return !(*this == point);
}
/**
 * setX function
 * @param x - the x coordinate of the point
 */
void Point::setX(int x) {
    Point::x = x;
}
/**
 * setY function
 * @param Y - the x coordinate of the point
 */
void Point::setY(int y) {
    Point::y = y;
}
/**
 * isObstacle method
 * @return - if the point is obstacle - true, else - false.
 */
bool Point::isObstacle() const {
    return obstacle;
}
/**
 * setObstacle method.
 * @param obstacle - true/false
 */
void Point::setObstacle(bool obstacle) {
    Point::obstacle = obstacle;
}

//BOOST_CLASS_EXPORT(Point);