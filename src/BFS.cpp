#include <queue>
#include "BFS.h"

/**
 * BFS default constuctor
 */
BFS::BFS() {}

/**
 * func name: shortestPathBFS.
 * using the BFS Algorithm for the shortest path.
 * we set for each son a 'dad' node during the algorithm to
 * get the exact path from start to end.
 * @param grid - our "map".
 * @param start - start node.
 * @param end - end node.
 * @return - the path in a deque.
 */
deque<Node*> BFS::shortestPathBFS(GridBase* grid, Node* start, Node* end) {
    queue <Node*> q;
    start->setVisited(true);
    q.push(start);
    deque<Node*> s;

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (node->isEqual(end)) {
            Node* startPoint = end;
            while (!startPoint->isEqual(start)) {
                s.push_front(startPoint);
                startPoint = startPoint->getDad();
            }
            s.push_front(startPoint);
            return s;
        }

        vector<Node*> sons = grid->getSons(node);

        for (int i = 0; i < (int)sons.size(); i++) {
            if (!sons[i]->getIsVisited()) {
                sons[i]->setVisited(true);
                q.push(sons[i]);
                sons[i]->setDad(node);
            }
        }
    }
    return s;
}
