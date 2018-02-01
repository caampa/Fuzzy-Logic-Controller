#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
using namespace std;

class Rule;
/**
* Class that represents the rule based table into a fuzzy logic system.
*/

class Table {
private:
	vector<Rule>* table;

public:
	/* Constructor */
	Table(vector<Rule>* table);

	/* Getter */
	vector<Rule>* getTable();

	/* Setter */
	void setTable(vector<Rule>* newtable);

};

#endif