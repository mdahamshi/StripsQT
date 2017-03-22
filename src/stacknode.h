#ifndef STACKNODE_H
#define STACKNODE_H
#include "genpred.h"
#include "predicate.h"

#include "action.h"

class StackNode{
    public:
    int type;
    Genpred gpred;
    list<Genpred> gpredconj;
    Predicate pred;
    list<Predicate> conj;
    Action action;

    StackNode(int type2=0){
        type=type2;
    }

    StackNode(const StackNode& x){
        type=x.type;
        pred=Predicate(x.pred);
        conj=x.conj;
        action=Action(x.action);
        gpred=Genpred(x.gpred);
        gpredconj=x.gpredconj;
    }


};
#endif // STACKNODE_H
