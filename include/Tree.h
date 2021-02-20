#ifndef TREE_H_
#define TREE_H_

#include <vector>

using namespace std;

class Session;

class Tree{
public:
    Tree(int rootLabel);

    Tree(const Tree& other);
    virtual ~Tree();
    Tree(Tree &&other);
    const Tree& operator=(const Tree& other);
    const Tree& operator=(Tree&& other);

    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    const int& getNode();
    virtual Tree* clone() const = 0; //creates a new pointer to the object
    vector<Tree*>& getChildren();

protected:
    int node;
    std::vector<Tree*> children;

    void clear();
    void copyChildren(const Tree& other);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif