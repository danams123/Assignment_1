#include "../include/Tree.h"
#include "../include/Session.h"

//Tree class

//Constructor
Tree::Tree(int rootLabel):node(rootLabel),children(){}

//Copy Constructor
Tree::Tree(const Tree& other): node(other.node), children(){
    copyChildren(other);
}

//Destructor
Tree::~Tree(){
    clear();
}

//Move Constructor
Tree::Tree(Tree &&other):node(other.node), children(move(other.children)){}

//Copy Assignment Operator
const Tree& Tree::operator=(const Tree& other){
    if(this != &other){
        this->clear();
        node = other.node;
        copyChildren(other);
    }
    return *this;
}

//Move Assignment Operator
const Tree& Tree::operator=(Tree&& other){
    if(this != &other){
        this->clear();
        node = other.node;
        children = move(other.children);
    }
    return *this;
}

void Tree::clear() {
    if(&children) {
        for (Tree *elem: children) {
            if (elem != nullptr) {
                delete (elem);
                elem = nullptr;
            }
        }
        children.clear();
    }
}

void Tree::copyChildren(const Tree &other) {
    for(Tree* elem: other.children){
        children.push_back(elem->clone());
    }
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

Tree* Tree::createTree(const Session& session, int rootLabel){
    if(session.getTreeType()==MaxRank){
        return new MaxRankTree(rootLabel);
        }

    else if(session.getTreeType()==Cycle){
        return new CycleTree(rootLabel,session.getCycle());
    }
    else {
        return new RootTree(rootLabel);
    }
}

const int& Tree::getNode(){return node;}

vector<Tree*>& Tree::getChildren() {return children;}


//CycleTree class
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    //in order to access the children field of this
    Tree* copy = this;
    for (int i = 0; (i < currCycle) && (!copy->getChildren().empty()); ++i) {
        copy = copy->getChildren().at(0);
    }
    return copy->getNode();
}

Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}


//MaxRankTree class
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){}

/*
 using BFS to scan the tree in the order of smallest to biggest depth and index of node,
 so that the only check will be of maximum children
 */
int MaxRankTree::traceTree() {
    unsigned int output = node;
    unsigned int maxSize = this->getChildren().size();
    vector<Tree*> queue;
   queue.push_back(this);
   while(!queue.empty()){
       Tree* curr = queue.at(0);
       queue.erase(queue.begin());
       for(Tree* elem: curr->getChildren()){
           queue.push_back(elem);
           if(elem->getChildren().size() > maxSize){
               output = elem->getNode();
               maxSize = elem->getChildren().size();
           }
       }
   }
   return output;
}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

//RootTree class
RootTree::RootTree(int rootLabel): Tree(rootLabel){}

int RootTree::traceTree(){
    return this->getNode();
}

Tree* RootTree::clone() const {
    return new RootTree(*this);
}