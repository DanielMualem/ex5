
#ifndef EX1_1_GRID_H
#define EX1_1_GRID_H

#include <iostream>
#include <list>
#include <vector>
#include "Node.h"

using namespace std;
/**
 * GridBase class (Abstract).
 * The base of every grid.
 */
class GridBase {

public:
    GridBase();
    virtual vector<Node*> getSons(Node *node) = 0;
    virtual void shortestPath(GridBase* grid, Node* start, Node* end) = 0;
    virtual void setAllVisited(bool isVisited) = 0;
    virtual void buildGrid() = 0;
};

#endif //EX1_1_GRID_H