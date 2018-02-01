#include "stdafx.h"
#include "Rule.h"
#include "Function.h"
#include "Graph.h"
#include "FuzzyLogic.h"

/** FUZZY LOGIC - RIGHT EDGE FOLLOWING **/
void FuzzyRightEdgeController();
vector<Rule*>* FuzzyRightEdgeTable();
vector<Graph*>* FuzzyRightEdgeGraphs();

/** FUZZY LOGIC - OBSTACLE AVOIDANCE **/
void FuzzyObstacleAvoidanceController();
vector<Rule*>* FuzzyObstacleAvoidanceTable();
vector<Graph*>* FuzzyObstacleAvoidanceGraphs();

/** INTEGRATION OF BOTH **/
void FuzzyBoth();