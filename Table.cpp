#include "stdafx.h"
#include "Table.h"

/**
* Class that represents the rule based table into a fuzzy logic system.
*/
Table::Table(vector<Rule>* table)
	:table(table)
{
}

/* Getters */
vector<Rule>* Table::getTable() {
	return this->table;
}

/* Setter */
void Table::setTable(vector<Rule>* newtable) {
	this->table = newtable;
}