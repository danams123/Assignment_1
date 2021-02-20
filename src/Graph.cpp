#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/Session.h"


Graph::Graph(std::vector<std::vector<int>> matrix): edges(matrix), nodes(){
    vector<int> copy(matrix.size());
    nodes = copy;
}

Tree* Graph::BFS(const Session &session, int rootLabel) const {
    // so i won't visit the same node twice
    vector<bool> visited(nodes.size());
    visited[rootLabel] = true;
    // creating the breadth check on the graph
    vector<Tree*> queue;
    Tree* output = Tree::createTree(session, rootLabel);
    queue.push_back(output);
    while (!queue.empty()) {
        Tree* currNode = queue.at(0);
        queue.erase(queue.begin());
        vector<int> neighbours = session.getGraph().neighboursOf(currNode->getNode());
        for(vector<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++){
            if (!visited[*it]) {
                visited[*it] = true;
                Tree* n = Tree::createTree(session, *it);
                currNode->addChild(*n);
                delete n;
                //calling addchild that uses clone, to keep the same pointer we need to get it out from children again
                queue.push_back(currNode->getChildren().back());
            }
        }
    }
    return output;
}

void Graph:: infectNode(unsigned int nodeInd) {
    if (nodeInd >= 0 && nodeInd < nodes.size()) {
        nodes[nodeInd] = 2;
    }
}

bool Graph:: isInfected(unsigned int nodeInd) const{
    if(nodes[nodeInd] == 2){
        return true;
    }
    return false;
}

// stage 2 - node isn't infected but is a carrier now, when it's adjacent to an infected node
void Graph::carrierNode(unsigned int nodeInd) {
    if (nodeInd >= 0 && nodeInd < nodes.size()) {
        nodes[nodeInd] = 1;
    }
}

bool Graph::isCarrier(unsigned int nodeInd) const{
    if(nodes[nodeInd] == 1){
        return true;
    }
    return false;
}


void Graph::delEdge(int node1, int node2) {
    edges[node1][node2] = 0;
    edges[node2][node1] = 0;
}

vector<int> Graph::neighboursOf(int node) const {
   vector<int> neighbours;
    for(unsigned int i = 0; i < edges[node].size(); ++i){
        if(edges[node][i] == 1){
            neighbours.push_back(i);
        }
    }
    return neighbours;
}

const vector<vector<int>>& Graph::getEdges() {return edges;}