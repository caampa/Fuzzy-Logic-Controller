#ifndef GRAPH_H_
#define GRAPH_H_

#include <string.h>
#include <vector>
using namespace std;

class Function;

/**
* Class that represents the complete graph for a membership function.
*/

class Graph {
private:
	string ID;							/* Name of the Input or Output values being represented in the graph */
	vector<Function*>* functions;		/* Set of functions that represents the graph of membership */


public:
	/* Constructor */
	Graph(string ID, vector<Function*>* functions);

	/* Getters */
	string getID();
	vector<Function*>* getFuntions();

	/* Setters */
	void setID(string newname);
	void setFunctions(vector<Function*>* newf);
};
#endif