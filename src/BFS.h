
#ifndef EX1_1_BFS_H
#define EX1_1_BFS_H


#include "Node.h"
#include "GridBase.h"
#include <deque>
/**
 * BFS Class.
 * stores the Breadth first search Algorithm.
 */
class BFS {
public:
    BFS();
    deque<Node*> shortestPathBFS(GridBase* grid, Node* start, Node* end);
};


#endif //EX1_1_BFS_H
