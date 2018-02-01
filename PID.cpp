#include "stdafx.h"
#include "PID.h"


/** GLOBAL VARIABLES **/
double perfect_distance = 300;
//double kp = 0.09, ki = 0.000001, kd = 0.00000;
double kp = 0.399, ki = 0.000001, kd = 0.00035;
double ed = 0, ei = 0, eprev = 0;
double base_velocity = 150;


void PIDcontroller() {

	/** SENSORS CONFIGURATION **/
	double sonar_range[NUM_SENSORS];
	ArSensorReading *sonar_sensor[NUM_SENSORS];

	while (true) {

		/*Recollection of the sonar distances*/
		for (int i = 0; i < NUM_SENSORS; i++) {
			sonar_sensor[i] = robot->getSonarReading(i);
			sonar_range[i] = sonar_sensor[i]->getRange();
		}

		double s4 = sonar_range[4];
		double s5 = sonar_range[5];
		double s6 = sonar_range[6];
		double s7 = sonar_range[7];
		double sfinal;

		//FOR THE REAL ROBOT
		/*if (s4 > 800) s4 = 799;
		if (s5 > 800) s5 = 799;
		if (s6 > 800) s6 = 799;
		if (s7 > 800) s7 = 799;*/


		if (s4 < s5) {
			if (s4 < s6) {
				if (s4 < s7) {
					sfinal = s4;
				}
				else {
					sfinal = s7;
				}
			}
			else {
				if (s6 < s7) {
					sfinal = s6;
				}
				else {
					sfinal = s7;
				}
			}

		}
		else {
			if (s5 < s6) {
				if (s5 < s7) {
					sfinal = s5;
				}
				else {
					sfinal = s7;
				}
			}
			else {
				if (s6 < s7) {
					sfinal = s6;
				}
				else {
					sfinal = s7;
				}
			}
		}

		PIDformula(sfinal);
	}
}

void PIDformula(double current_distance) {

	double error = perfect_distance - current_distance;

	ei = ei + error;
	ed = error - eprev;
	eprev = error;

	double pid = (kp * error) + (kd * ed) + (ki * ei);
	double left_wheel = 0;
	double right_wheel = 0;

	left_wheel = base_velocity - (pid / 2);
	right_wheel = base_velocity + (pid / 2);

	cout << "Perfect: " << perfect_distance << " - Current: " << current_distance << endl;
	cout << "Left: " << left_wheel << " - Right: " << right_wheel << endl;

	robot->setVel2(left_wheel, right_wheel);

}