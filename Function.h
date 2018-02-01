#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string.h>
using namespace std;


/**
* Class that rerpresents the degree of membership for a set of crisp values into a Fuzzy group 
*/

class Function {
private:
	string label;			/* Fuzzy name of the function*/
	double a;				/* Starting point of the function */
	double b;				/* Second point of the function */
	double c;				/* Third point of the function */
	double d;				/* Ending point of the function */

public:
	/* Constructor */
	Function(string label, double a, double b, double c, double d);

	/* Getters */
	string getLabel();
	double getA();
	double getB();
	double getC();
	double getD();

	/* Setters */
	void setLabel(string l);
	void setA(double x);
	void setB(double x);
	void setC(double x);
	void setD(double x);

	/* Others */
	double getMembershipValue(double z);
	double getCentroid();
};

#endif