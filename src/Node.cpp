#include "Node.h"
/**
 * Node default constructor.
 */
Node::Node() {
}
/**
 * operator << overloading.
 * @param os - stream.
 * @param obj - Node obj.
 * @return - the stream.
 */
ostream& operator<<(ostream& os, const Node& obj) {
    os << obj.toString() << endl;
    return os;
}
/**
 * Node dtor.
 */
Node::~Node() {}



