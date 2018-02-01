#ifndef RULE_H_
#define RULE_H_

#include <string.h>
using namespace std;

/**
* Class that represents a specific rule inside of a rule based table.
*/

class Rule {
private:
	int ID;								/* Position of the rule in the table */
	string front_sensor, back_sensor;	/* Fuzzy value for the right front and back sensor according to its distance */
	string left_wheel, right_wheel;		/* Fuzzy value for the left and right wheel according to its speed */

public:
	Rule(int ID, string front_sensor, string back_sensor, string left_wheel, string right_wheel);

	/* Getters */
	int getID();
	string getFrontSensor();
	string getBackSensor();
	string getLeftWheel();
	string getRightWheel();

};

#endif