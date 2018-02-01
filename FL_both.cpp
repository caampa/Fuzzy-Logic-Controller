#include "stdafx.h"
#include "FL_.h"

void FuzzyBoth() {

	/** SENSORS CONFIGURATION **/
	int sonar_range[NUM_SENSORS];
	ArSensorReading *sonar_sensor[NUM_SENSORS];
	double left_wheel = 0.0, right_wheel = 0.0;
	vector<double> speed;

	/** FUZZY LOGIC CONFIGURATION **/

	//Right Edge Following
	vector<Graph*>* graphsRE = FuzzyRightEdgeGraphs();
	vector<Rule*>* tableRE = FuzzyRightEdgeTable();
	FuzzyLogic* fuzzyRE = new FuzzyLogic(graphsRE, tableRE);

	//Obstacle Avoidance
	vector<Graph*>* graphsOA = FuzzyObstacleAvoidanceGraphs();
	vector<Rule*>* tableOA = FuzzyObstacleAvoidanceTable();
	FuzzyLogic* fuzzyOA = new FuzzyLogic(graphsOA, tableOA);

	while (true) {

		/* Recollection of the sonar distances */
		for (int i = 0; i < NUM_SENSORS; i++) {
			sonar_sensor[i] = robot->getSonarReading(i);
			sonar_range[i] = sonar_sensor[i]->getRange();
		}

		double s3 = sonar_range[3];
		double s4 = sonar_range[4];
		double s5 = sonar_range[5];
		double s6 = sonar_range[6];
		double s7 = sonar_range[7];

		if (s3 > 800) s3 = 799;
		if (s4 > 800) s4 = 799;
		if (s5 > 800) s5 = 799;
		if (s6 > 800) s6 = 799;
		if (s7 > 800) s7 = 799;

		//Pick the minimun between the frontal sensors
		double min_f;
		if (s3 < s4) min_f = s3;
		else  min_f = s4;

		/** ACTIVATION OF OBSTACLE AVOIDANCE **/
		if (min_f < 250) {

			//Pick the minimun between the right sensors
			double min_r;
			if (s5 < s6) {
				if (s5 < s7) min_r = s5;
				else min_r = s7;
			}
			else {
				if (s6 < s7) min_r = s6;
				else min_r = s7;
			}
			//FOR THE REAL ROBOT
			//if (min_r > 800) min_r = 799;

			/* Calculation of the wheel motor speed using Fuzzy Logic */
			speed = fuzzyOA->FuzzyLogicAlgorithm(min_f, min_r);
		}
		/** KEEP FOLLOWING THE RIGHT EDGE OF THE WALL **/
		else {
			/*//FOR THE REAL ROBOT
			if (sonar_range[6] > 800) {
			sonar_range[6] = 400;

			}
			if (sonar_range[7] > 800) {
			sonar_range[7] = 799;
			sonar_range[6] = 799;

			}*/
			/* Calculation of the wheel motor speed using Fuzzy Logic */
			speed = fuzzyRE->FuzzyLogicAlgorithm(sonar_range[6], sonar_range[7]);
		}

		left_wheel = speed[0];
		right_wheel = speed[1];

		/* Seting up velocity to the robot's wheels */
		cout << "SENSOR-FRONT: " << sonar_range[6] << " - SENSOR-RIGHT: " << sonar_range[7] << endl;
		cout << "LEFT: " << left_wheel << " - RIGHT: " << right_wheel << endl;
		robot->setVel2(left_wheel, right_wheel);
	}
}