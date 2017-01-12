#ifndef EX1_1_NODEBASE_H
#define EX1_1_NODEBASE_H

#include <iostream>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

using namespace std;
/**
 * Node Class (Abstract).
 * The base of every node.
 */
class Node {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){}
public:
    Node();
    virtual Node* getNode() = 0;
    virtual void setVisited(bool isVisited) = 0;
    virtual bool getIsVisited() const = 0;
    virtual Node* getDad() const = 0;
    virtual void setDad(Node* dad) = 0;
    virtual bool isEqual(Node* node) = 0;
    virtual string toString() const = 0;
    friend ostream& operator<<(ostream& os, const Node& obj);
    virtual ~Node();
};

//BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node);
#endif //EX1_1_NODEBASE_H