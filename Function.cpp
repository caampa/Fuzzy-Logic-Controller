#include "stdafx.h"
#include "Function.h"

/**
* Class that rerpresents the degree of membership for a set of crisp values into a Fuzzy group
*/

Function::Function(string label, double a, double b, double c, double d)
	:label(label), a(a), b(b), c(c), d(d)
{
}

/* Getters */
string Function::getLabel() {
	return this->label;
}
double Function::getA() {
	return this->a;
}
double Function::getB() {
	return this->b;
}
double Function::getC() {
	return this->c;
}
double Function::getD() {
	return this->d;
}

/* Setters */
void Function::setLabel(string l) {
	this->label = l;
}
void Function::setA(double x) {
	this->a = x;
}
void Function::setB(double x) {
	this->b = x;
}
void Function::setC(double x) {
	this->c = x;
}
void Function::setD(double x) {
	this->d = x;
}

/* Others */

/**
* Method that given a point Z, it calculates the membership value for that point inside of a specific function of the graph.
*/
double Function::getMembershipValue(double z) {
	double rising_edge = ((z - a) / (b - a));
	double falling_edge = ((d - z) / (d - c));

	//LEFT SHOULDER
	if (a == b) {
		if (z <= c) {
			return 1;
		}
		else if ((z > c) && (z < d)) {
			return falling_edge;
		}
	}
	//TRIANGLE
	else if (b == c) {
		if (z == b) {
			return 1;
			//Rising edge of the triangle
		} else if ((z > a) && (z < b)) {
			return rising_edge;
		//Falling edge of the triangle
		} else if ((z > b) && (z < d)) {
			return falling_edge;
		}
	}
	
	//TRAPEZOID
	else if ((a != b) && (b != c) && (c != d)) {
		if ((z >= b) || (z <= c)) {
			return 1;
		}//Rising edge of the trapeziod
		else if ((z > a) && (z < b)) {
			return rising_edge;
			//Falling edge of the triangle
		}
		else if ((z > c) && (z < d)) {
			return falling_edge;
		}
	}
	//RIGHT SHOULDER
	else if (c == d) {
		if (z >= b) {
			return 1;
		}
		else if ((z > a) && (z < b)) {
			return rising_edge;
		}
	}
	return NULL;
}

/**
* Method that calculate the centroid of a specific function inside of the graph.
*/
double Function::getCentroid() {
	return (a + d) / 2;
}