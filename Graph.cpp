#include "stdafx.h"
#include "Graph.h"

/**
* Class that represents the complete graph for a membership function.
*/

Graph::Graph(string ID, vector<Function*>* functions)
	:ID(ID), functions(functions)
{
}

/* Getters */
string Graph::getID() {
	return this->ID;
}
vector<Function*>* Graph::getFuntions() {
	return this->functions;
}

/* Setters */
void Graph::setID(string newname) {
	this->ID = newname;
}
void Graph::setFunctions(vector<Function*>* f) {
	this->functions = f;
}