

#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "iostream"
#include "fstream"
#include "json.hpp"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

using namespace std;

class Session{

public:
    Session(const std::string& path);
    Session(const Session& other);
    virtual ~Session();
    Session(Session &&other);
    const Session& operator=(const Session& other);
    const Session& operator=(Session&& other);

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    const Graph& getGraph() const;

    void enqueueInfected(int node);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCycle() const;
    void setCycle(const int& c);
    void setSick(const int& node);
    const vector<int>& getQueue();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    vector<int> queue;
    vector<int> sick;

    void clear();
    void copyAgents(const Session& other);
};

#endif
