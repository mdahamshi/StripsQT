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
#include "globavars.h"
extern std::stack<StackNode> strips ;
extern std::list<Predicate> keep_predicates ;
extern bool foundWall;

int firstHurestic(int);
bool chck_for_goal(Action act, Predicate pred);
bool conj_sat(list<Predicate> conj);
std::string gpredToString(Genpred gpred);
int getDoorDir(int);
std::string actToString(Action act);
int minusAct(int);
std::string predToString(Predicate pred);
bool gpred_conj_sat(list<Genpred> conj);
bool gpred_sat(Genpred);
bool findInList(Predicate,list<Predicate>);
void initialize_goals();
int moveThroughThirdDoor(Furniture,int);
int moveThroughFirstDoor(Furniture,int);
int moveThroughSecondDoor(Furniture,int);
void conj_print(list<Predicate> conj);
void Keep(list<Predicate>);
bool IsInCommon(list<Predicate>,list<Predicate>);
int operation_rank(int,int);

#endif // FUNCTIONS_H
