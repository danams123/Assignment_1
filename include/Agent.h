#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;

class Agent{
public:
    Agent();
    virtual ~Agent() = default;

    virtual void act(Session& session)=0;
    virtual Agent* clone() const = 0; //creates a new pointer to the object
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual void act(Session& session);
    virtual Agent* clone() const;

private:
    const int nodeInd;
};

#endif