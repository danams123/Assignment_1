#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Agent.h"

using namespace std;

class Session;
class Tree;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    Tree* BFS(const Session& session, int rootLabel) const;
    void infectNode(unsigned int nodeInd);
    bool isInfected(unsigned int nodeInd) const;
    void carrierNode(unsigned int nodeInd);
    bool isCarrier(unsigned int nodeInd) const;
    void delEdge(int node1, int node2);
    vector<int> neighboursOf(int node) const;
    const vector<vector<int>>& getEdges();

private:
    std::vector<std::vector<int>> edges;
    vector<int> nodes;
};

#endif