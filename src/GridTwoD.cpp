#include <stack>
#include "GridTwoD.h"
#include "BFS.h"

/**
 * GridTwoD default constructor.
 */
GridTwoD::GridTwoD() {
}

/**
 * GridTwoD constructor.
 * @param x - width
 * @param y - height
 */
GridTwoD::GridTwoD(int x, int y) {
    this->map = new Point*[x];
    for (int i = 0; i < x; i++) {
        this->map[i] = new Point[y];
    }

    this->size = Point(x, y);
}

/**
 * func name: buildGrid.
 * building the nodes accordingly to the size.
 */
void GridTwoD::buildGrid() {
    for (int i = 0; i < this->size.getX(); i++) {
        for (int j = 0; j < this->size.getY(); j++) {
            this->map[i][j] = Point(i, j);
        }
    }
}

/**
 * func name: getSons.
 * using the logic we got on the assignment (9,12,3,6).
 * @param node - Dad node.
 * @return - vector of sons
 */
vector<Node*> GridTwoD::getSons(Node *node) {
    vector<Node*> sons;
    Point* point = (Point*)node->getNode();
    int x = point->getX();
    int y = point->getY();

    if (x > 0) {
        if (!this->map[x-1][y].isObstacle()) {
            sons.push_back(&this->map[x-1][y]);
        }
    }
    if (y < this->size.getY() - 1) {
        if (!this->map[x][y+1].isObstacle()) {
            sons.push_back(&this->map[x][y+1]);
        }
    }
    if (x < this->size.getX() - 1) {
        if (!this->map[x+1][y].isObstacle()) {
            sons.push_back(&this->map[x+1][y]);
        }
    }
    if (y > 0) {
        if (!this->map[x][y-1].isObstacle()) {
            sons.push_back(&this->map[x][y-1]);
        }
    }
    return sons;
}
 /**
  * func name: setAllVisited.
  * @param isVisited - true or false.
  */
void GridTwoD::setAllVisited(bool isVisited) {
    for (int i = 0; i < this->size.getX(); i++) {
        for (int j = 0; j < this->size.getY(); j++) {
            this->map[i][j].setVisited(isVisited);
        }
    }
}

/**
 * func name: getGrid.
 * @return - the 2D grid.
 */
Point** GridTwoD::getGrid() {
    return this->map;
}

/**
 * func name: shortestPath.
 * print the shortest path.
 * @param grid - our "map".
 * @param start - start node.
 * @param end - end node.
 */
void GridTwoD::shortestPath(GridBase* grid, Node* start, Node* end) {
    BFS bfs;
    deque<Node*> s = bfs.shortestPathBFS(grid, start, end);
    while (!s.empty()) {
        cout << *s.front();
        s.pop_front();
    }

}
/**
 * GridTwoD distructor.
 */
GridTwoD::~GridTwoD() {
    for (int i = 0; i <  this->size.getX(); i++) {
        delete[] this->map[i];
    }

    delete[] this->map;
}
/**
 * getSize function
 * @return the size of the grid
 */
const Point GridTwoD::getSize() const {
    return size;
}
/**
 * addObstacle methos.
 * @param x - x val of the obstacle point
 * @param y - y val of the obstacle point
 */
void GridTwoD::addObstacle(int x, int y) {
    this->map[x][y].setObstacle(true);
}
/**
 * getPath function
 * @param start - the start point of the trip
 * @param end - the end point of the trip
 * @return the sortest path of the trip
 */
deque<Node*> GridTwoD::getPath(Node* start, Node* end){
    BFS bfs;
    return bfs.shortestPathBFS(this, start, end);
}