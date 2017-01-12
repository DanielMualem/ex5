#ifndef EX1_1_POINT_H
#define EX1_1_POINT_H

#include <iostream>
#include <boost/serialization/access.hpp>
#include "Node.h"
/**
 * Point Class.
 * x,y values demonstrate a 2D world.
 */
class Point : public Node {
private:
    int x;
    int y;
    bool isVisited;
    Node* dad;
    bool obstacle;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Node>(*this);
        ar & x;
        ar & y;
        ar & isVisited;
        ar & dad;
        ar & obstacle;
    }
public:
    Point();
    Point(int x, int y);
    Node* getNode();
    int getX() const;
    int getY() const;
    bool isEqual(Node* node);
    void setVisited(bool isVisited);
    void setDad(Node *dad);
    Node* getDad() const;
    bool getIsVisited() const;
    virtual ~Point();
    const Point operator+(const Point& point) const;
    bool operator==(const Point& point) const;
    bool operator!=(const Point& point) const;
    void setX(int x);
    void setY(int y);
    void setObstacle(bool obstacle);
    bool isObstacle() const;
    string toString() const;
};

#endif //EX1_1_POINT_H