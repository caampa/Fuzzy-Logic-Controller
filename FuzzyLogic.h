#include "stdafx.h"
//#include <vector>
//using namespace std;

class Graph;
class Rule;

/**
* Class that represents right edge following behaviour of a robot using Fuzzy Logic.
*/

class FuzzyLogic {
	private:
		vector<Graph*>* graphs;
		vector<Rule*>* table;

	public:
		/* Constructor */
		FuzzyLogic(vector<Graph*>* graficas, vector<Rule*>* table);

		/* Getters */
		vector<Graph*>* getGraphs();
		vector<Rule*>* getTable();
		Rule* getRule(int ID);

		/* Setters */
		void setGraphs(vector<Graph*>* newg);
		void setTable(vector<Rule*>* newt);

		/* Others */
		map <string, double> membershipValuesRFS(double crisp_rfs);
		map <string, double> membershipValuesRBS(double crisp_rbs);
		map <int, double> firingStrenght(map <string, double> mv_RFS, map <string, double> mv_RBS);
		vector<double> highDefuzzyfication(map <int, double> firing_strengths);
		vector<double> FuzzyLogicAlgorithm(double crisp_rfs, double crisp_rbs);
};
