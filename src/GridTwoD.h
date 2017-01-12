#ifndef EX1_1_GRIDTWOD_H
#define EX1_1_GRIDTWOD_H

#include <vector>
#include "GridBase.h"
#include "Point.h"
#include <deque>

/**
 * GridTwoD Class. implements GridBase.
 * has 2D array to store a 2D map of nodes.
 */
class GridTwoD : public GridBase {
private:
    Point **map;
    Point size;


public:
    GridTwoD();

    GridTwoD(int x, int y);

    void buildGrid();

    vector<Node *> getSons(Node *node);

    Point **getGrid();

    void setAllVisited(bool isVisited);

    void shortestPath(GridBase *grid, Node *start, Node *end);

    virtual ~GridTwoD();

    const Point getSize() const;

    void addObstacle(int x, int y);

    deque<Node*> getPath(Node *start, Node *end);
};

#endif //EX1_1_GRIDTWOD_H