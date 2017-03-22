#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
#include <stack>
#include <string>
#include <list>
#include "stacknode.h"
#include "globals.h"
//#include "predicate.h"
#include "action.h"
//#include "genpred.h"


bool chck_for_goal(Action act, Predicate pred);
bool conj_sat(list<Predicate> conj);
bool gpred_conj_sat(list<Genpred> conj);
bool gpred_sat(Genpred);
bool findInList(Predicate,list<Predicate>);
void initialize_goals();
void conj_print(list<Predicate> conj);
void Keep(list<Predicate>);
bool IsInCommon(list<Predicate>,list<Predicate>);
int operation_rank(int,int);

extern int nextobj;
#endif // FUNCTIONS_H
