#include "stdafx.h"
#include "FuzzyLogic.h"
#include "Graph.h"
#include "Function.h"
#include "Rule.h"


/**
* Class that represents the rule based table into a fuzzy logic system.
*/
FuzzyLogic::FuzzyLogic(vector<Graph*>* graphs, vector<Rule*>* table)
	:graphs(graphs), table(table)
{
}

/* Getters */
vector<Graph*>* FuzzyLogic::getGraphs() {
	return this->graphs;
}
vector<Rule*>* FuzzyLogic::getTable() {
	return this->table;
}

/* Setters */
void FuzzyLogic::setGraphs(vector<Graph*>* newg) {
	this->graphs = newg;
}
void FuzzyLogic::setTable(vector<Rule*>* newt) {
	this->table = newt;
}

/* Others */

/**
* Method that calcule all of the membership values for a crisp number regarding to the RIGHT FRONT SENSOR
*	crisp_rbs: Crisp value received from the right back sensor of the robot.
* Return: Label and degree of membership for each funcion where the crisp value appears.
*/
map <string, double> FuzzyLogic::membershipValuesRFS(double crisp_rfs) {
	map <string, double> mv; //Label and degree of membership

	//Pick the graph which represents the membership value of the RIGHT FRONT SENSOR
	for (vector<Graph*>::iterator it = this->getGraphs()->begin(); it != this->getGraphs()->end(); ++it) {
		if ((*it)->getID() == "RFS") {
			//Iterate every function(shape) of the graph that has a different label
			for (vector<Function*>::iterator shape = (*it)->getFuntions()->begin(); shape != (*it)->getFuntions()->end(); ++shape) {
				//Identify if the crisp value belongs this specific function of the graph
				if (crisp_rfs > (*shape)->getA() && crisp_rfs < (*shape)->getD()) {
					//Storing the label and membership value
					mv[(*shape)->getLabel()] = ((*shape)->getMembershipValue(crisp_rfs));
				}
			}
		}
	}
	return mv;
}

/**
* Method that calcule all of the membership values for a crisp number regarding to the RIGHT BACK SENSOR.
*	crisp_rbs: Crisp value received from the right back sensor of the robot.
* Return: Label and degree of membership for each funcion where the crisp value appears.
*/
map <string, double> FuzzyLogic::membershipValuesRBS(double crisp_rbs) {
	map <string, double> mv; //Label and degree of membership

	//Pick the graph which represents the membership value of the RIGHT FRONT SENSOR
	for (vector<Graph*>::iterator it = this->getGraphs()->begin(); it != this->getGraphs()->end(); ++it) {
		if ((*it)->getID() == "RBS") {
			//Iterate every function(shape) of the graph that has a different label
			for (vector<Function*>::iterator shape = (*it)->getFuntions()->begin(); shape != (*it)->getFuntions()->end(); ++shape) {
				//Identify if the crisp value belongs this specific function of the graph
				if (crisp_rbs > (*shape)->getA() && crisp_rbs < (*shape)->getD()) {
					//Storing the label and membership value
					mv[(*shape)->getLabel()] = ((*shape)->getMembershipValue(crisp_rbs));
				}
			}
		}
	}
	return mv;
}

/**
* Method that calcules the firing strength for all the membership values.
*	 mv_FS: Membership value and Label for all the functions where the rule is activated in the FRONT sensor's graph.
*	 mv_BS: Membership value and Label for all the functions where the rule is activated in the BACK sensor's grap.
*	Return: ID of the rule activated and the membership value chosen.
*/
map <int, double> FuzzyLogic::firingStrenght(map <string, double> mv_FS, map <string, double> mv_BS) {
	map <int, double> f;
	int num_rule = 0;

	//Iterate each Membership value for the FRONT SENSOR
	for (map <string, double>::iterator fs = mv_FS.begin(); fs != mv_FS.end(); ++fs) {
		//Iterate each Membership value for the BACK SENSOR
		for (map <string, double>::iterator bs = mv_BS.begin(); bs != mv_BS.end(); ++bs) {
			//Identify rule activated
			for (vector<Rule*>::iterator rule = this->getTable()->begin(); rule != this->getTable()->end(); ++rule) {
				if (((*rule)->getFrontSensor() == fs->first) && ((*rule)->getBackSensor() == bs->first)){
					num_rule = (*rule)->getID();
				}
			}
			//We choose the minimum value between both
			if (fs->second > bs->second) {
				f[num_rule] = (bs->second);
			}else {
				f[num_rule] = (fs->second);
			}
		}
	}
	return f;
}

/**
* Method that given an identificator, returns the rule asiciated
*	 ID: identificator of the rule
*	Return: Rule
*/
Rule*  FuzzyLogic::getRule(int ID) {
	for (vector<Rule*>::iterator it = this->getTable()->begin(); it != this->getTable()->end(); ++it) {
		if ((*it)->getID() == ID)
			return (*it);
	}
	return NULL;
}

/**
* Method that calcules the speed of the wheel of the robot
*	 firing_strengths: Firing strengths
*	Return: The values of the LEFT speed of the robot (first element of the array) and the RIGHT speed of the robot (second element of the array)
*/
vector<double>  FuzzyLogic::highDefuzzyfication(map <int, double> firing_strengths) {
	double numerator = 0.0, denominator = 0.0;
	double LW = 0.0; //Final motor speed of the left wheel
	double RW = 0.0; //Final motor speed of the right wheel
	vector<double> final_speeds;

	
	for (vector<Graph*>::iterator it = this->getGraphs()->begin(); it != this->getGraphs()->end(); ++it) {
		/* LEFT WHEEL */
		//Pick the graph which represents the membership value of the LEFT MOTOR SPEED
		if ((*it)->getID() == "LW") {
			//Iterate each firing strenght value
			for (map<int, double>::iterator fs = firing_strengths.begin(); fs != firing_strengths.end(); ++fs) {
				//Get the rule fired
				Rule* r = this->getRule(fs->first);
				//Iterate each function(shape) of the graph until find that one of the same label that the rule has
				for (vector<Function*>::iterator shape = (*it)->getFuntions()->begin(); shape != (*it)->getFuntions()->end(); ++shape) {
					if ((*shape)->getLabel() == r->getLeftWheel()) {
						//Calculate centroid of the shape
						double centroid = (*shape)->getCentroid();
						numerator += fs->second * centroid;
					}
				}
				//Sum of all firinf strengths values
				denominator += fs->second;
			}
			LW = numerator / denominator;
		}
		/* RIGHT WHEEL */
		//Pick the graph which represents the membership value of the RIGHT MOTOR SPEED
		else if ((*it)->getID() == "RW") {
			numerator = 0.0, denominator = 0.0; //Reset

			//Iterate each firing strenght value
			for (map<int, double>::iterator fs = firing_strengths.begin(); fs != firing_strengths.end(); ++fs) {
				//Get the rule fired
				Rule* r = this->getRule(fs->first);
				//Iterate each function(shape) of the graph until find that one of the same label that the rule has
				for (vector<Function*>::iterator shape = (*it)->getFuntions()->begin(); shape != (*it)->getFuntions()->end(); ++shape) {
					if ((*shape)->getLabel() == r->getRightWheel()) {
						//Calculate centroid of the shape
						double centroid = (*shape)->getCentroid();
						numerator += fs->second * centroid;
					}
				}
				//Sum of all firinf strengths values
				denominator += fs->second;
			}
			RW = numerator / denominator;
		}
	}
	final_speeds.push_back(LW);
	final_speeds.push_back(RW);
	return final_speeds;
}

/**
* Method that implements all the steps for a Fuzzy Logic algorithm.
*   crisp_rfs: Crisp value received from the (right) front sensor of the robot.
*	crisp_rbs: Crisp value received from the (right) back sensor of the robot.
* Return: Speed for both wheels of the robot.
*/
vector<double> FuzzyLogic::FuzzyLogicAlgorithm(double crisp_rfs, double crisp_rbs) {

	/* STEP1- Calculation of the membership values for both sonar's distances */
	map <string, double> mv_RFS = this->membershipValuesRFS(crisp_rfs);
	map <string, double> mv_RBS = this->membershipValuesRBS(crisp_rbs);

	/* STEP2- Firing strennght */
	map <int, double> firing_strengths = this->firingStrenght(mv_RFS, mv_RBS);

	/* STEP3- High Defuzzification */
	vector<double> speed = this->highDefuzzyfication(firing_strengths);

	return speed;
}