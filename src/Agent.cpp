#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"

//Agent class
Agent::Agent() {}

//ContactTracer class
ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {
    int sick = session.dequeueInfected();
    if(sick != -1) { //if the queue is empty
        Tree *s(session.getGraph().BFS(session, sick));
        int spreader = s->traceTree();
        delete s;
        vector<int> toCut = session.getGraph().neighboursOf(spreader);
        Graph g = session.getGraph();
        for (int cut: (toCut)) {
            g.delEdge(spreader, cut);
        }
        session.setGraph(g);
    }
}

Agent* ContactTracer::clone() const{
    return new ContactTracer(*this);
}

//Virus class
Virus::Virus(int nodeInd):nodeInd(nodeInd) {}

void Virus::act(Session &session) {
    Graph g = session.getGraph();
    vector<int> toInfect = session.getGraph().neighboursOf(nodeInd);
    for (unsigned int infect: (toInfect)) {
        //only infecting nodes that are healthy because the rest are in the queue/agents vector already
        if (!g.isCarrier(infect) && !g.isInfected(infect)) {
            g.carrierNode(infect);
            Virus n(infect);
            session.addAgent(n);
            //the virus infects only one neighbour in a cycle
            break;
        }
    }
 //changing the node, which is definitely in carrier mode, to infected and updating the queue and sick vectors
    if(!session.getGraph().isInfected(nodeInd)){
        session.enqueueInfected(nodeInd);
        g.infectNode(nodeInd);
        session.setSick(nodeInd);

    }
    session.setGraph(g);
}

Agent* Virus::clone() const{
    return new Virus(*this);
}
