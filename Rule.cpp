#include "stdafx.h"
#include "Rule.h"

/**
* Class that represents a specific rule inside of a rule based table.
*/

Rule::Rule(int ID, string front_sensor, string back_sensor, string left_wheel, string right_wheel)
	:ID(ID), front_sensor(front_sensor), back_sensor(back_sensor), left_wheel(left_wheel), right_wheel(right_wheel)
{
}

/* Getters */
int Rule::getID() {
	return this->ID;
}
string Rule::getFrontSensor() {
	return this->front_sensor;
}
string Rule::getBackSensor() {
	return this->back_sensor;
}
string Rule::getLeftWheel() {
	return this->left_wheel;
}
string Rule::getRightWheel() {
	return this->right_wheel;
}
