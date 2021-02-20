
#include "../include/Session.h"
#include "../include/Graph.h"
#include "../include/Agent.h"
#include "../include/Tree.h"

using namespace std;

//Constructor
Session::Session(const std::string& path): g({}) ,treeType() ,agents() ,cycle(0) ,queue() ,sick(){
    //input json
    std::ifstream i(path);
    nlohmann::json j;
    i >> j;
    i.close();

    if(j["tree"] == "R"){treeType = Root;}
    else if(j["tree"] == "M"){treeType = MaxRank;}
    else{treeType = Cycle;}

    g = Graph(j["graph"]);
    for(auto &elem: j["agents"]){
        if(elem[0] == "V"){
            agents.push_back(new Virus(elem[1]));
            /*
             every virus that enters the agents list in the 0 iteration has to be a carrier so when act()
             is called it will work properly on the virus
             */
            g.carrierNode(elem[1]);
        }
        else{
            agents.push_back(new ContactTracer());
        }
    }
}

//Copy Constructor
Session::Session(const Session& other): g(other.g), treeType(other.treeType), agents(), cycle(other.cycle),
queue(other.queue),sick(other.sick){
    copyAgents(other);
}

//Destructor
Session::~Session() {
    clear();
}

//Move Constructor
Session::Session(Session &&other):g(move(other.g)), treeType(other.treeType), agents(move(other.agents)), cycle(other.cycle),
 queue(move(other.queue)), sick(move(other.sick)){}

//Copy Assignment Operator
const Session& Session::operator=(const Session& other){
    if(this != &other){
        this->clear();
        g = other.g;
        treeType = other.treeType;
        copyAgents(other);
        cycle = other.cycle;
        queue = other.queue;
        sick = other.sick;
    }
    return *this;
}

//Move Assignment Operator
const Session& Session:: operator=(Session&& other){
    if(this != &other){
        this->clear();
        g = move(other.g);
        treeType = other.treeType;
        agents = move(other.agents);
        cycle = other.cycle;
        queue = move(other.queue);
        sick = move(other.sick);
    }
    return *this;
}

void Session::clear(){
    if(&agents) {
        for (Agent *elem: agents) {
            if (elem != nullptr) {
                delete (elem);
                elem = nullptr;
            }
        }
        agents.clear();
    }
}

void Session::copyAgents(const Session& other){
    for(Agent* elem: other.agents){
        agents.push_back(elem->clone());
    }
}

void Session::simulate(){
    unsigned int check = agents.size();
    bool pass = true;
    //pass helps to pass the first iteration in which the check condition isn't true
    while((check != agents.size())||(pass)){
        pass = false;
        check = agents.size();
        //agents are added during the iteration, check keeps it const
        for (unsigned int i = 0; i < check; ++i) {
            agents[i]->act(*this);
        }
        cycle ++;
    }
    // for multiple runs
    queue.clear();
    //output json
    nlohmann::json j;
    j["infected"] = sick;
    j["graph"] = g.getEdges();
    ofstream o("./output.json");
    o << j;
    o.close();
}

void Session::addAgent(const Agent& agent) {
    // clone helps to handle plural inheriting classes to Agent
   agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {g = graph;}

const Graph& Session::getGraph() const {return g;}

void Session::enqueueInfected(int node) {
    queue.push_back(node);
}

int Session::dequeueInfected() {
    if(!queue.empty()) {
        int output(queue.at(0));
        queue.erase(queue.begin());
        return output;
    }
    return -1;
}

TreeType Session::getTreeType() const {return treeType;}

int Session::getCycle() const {return cycle;}

void Session::setCycle(const int& c) {
    cycle = c;
}

void Session::setSick(const int &node) {
    sick.push_back(node);
}

const vector<int>& Session::getQueue() {return queue;}