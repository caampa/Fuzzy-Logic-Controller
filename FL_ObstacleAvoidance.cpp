#include "stdafx.h"
#include "FL_.h"

void FuzzyObstacleAvoidanceController() {

	/** SENSORS CONFIGURATION **/
	int sonar_range[NUM_SENSORS];
	ArSensorReading *sonar_sensor[NUM_SENSORS];
	double left_wheel = 0.0, right_wheel = 0.0;

	/** FUZZY LOGIC CONFIGURATION **/
	vector<Graph*>* graphs = FuzzyObstacleAvoidanceGraphs();
	vector<Rule*>* table = FuzzyObstacleAvoidanceTable();

	FuzzyLogic* fuzzy = new FuzzyLogic(graphs, table);

	while (true) {
		/* Recollection of the sonar distances */
		for (int i = 0; i < NUM_SENSORS; i++) {
			sonar_sensor[i] = robot->getSonarReading(i);
			sonar_range[i] = sonar_sensor[i]->getRange();
		}

		//FOR THE REAL ROBOT
		double s0 = sonar_range[0];
		double s1 = sonar_range[1];
		double s2 = sonar_range[2];
		double s3 = sonar_range[3];
		double s4 = sonar_range[4];
		double s5 = sonar_range[5];
		double s6 = sonar_range[6];
		double s7 = sonar_range[7];


		if (s0 > 800) s0 = 799;
		if (s1 > 800) s1 = 799;
		if (s2 > 800) s2 = 799;
		if (s3 > 800) s3 = 799;
		if (s4 > 800) s4 = 799;
		if (s5 > 800) s5 = 799;
		if (s6 > 800) s6 = 799;
		if (s7 > 800) s7 = 799;

		//Pick the minimun between the left sensors
		double min_l;
		if (s0 < s1) {
			if (s0 < s2) min_l = s0;
			else min_l = s2;
		}
		else {
			if (s1 < s2) min_l = s1;
			else min_l = s2;
		}
		//Pick the minimun between the frontal sensors
		double min_f;
		if (s3 < s4) min_f = s3;
		else  min_f = s4;
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

		/*if (min_l < min_f)
		min_f = min_l;*/
		/* Calculation of the wheel motor speed using Fuzzy Logic */
		vector<double> speed = fuzzy->FuzzyLogicAlgorithm(min_f, min_r);
		left_wheel = speed[0];
		right_wheel = speed[1];

		/* Seting up velocity to the robot's wheels */
		cout << "SENSOR-FRONT: " << min_f << " - SENSOR-RIGHT: " << min_r << endl;
		cout << "LEFT: " << left_wheel << " - RIGHT: " << right_wheel << endl;
		robot->setVel2(left_wheel, right_wheel);
	}
}

vector<Graph*>* FuzzyObstacleAvoidanceGraphs() {

	/** GRAPH CREATION  **/
	vector<Graph*>* graphs = new vector<Graph*>();

	/* Right FRONT Sensor */
	vector<Function*>* v_rfs = new vector<Function*>();
	//Left shoulder
	Function* ls_front = new Function("CLOSE", 0, 0, 250, 400);
	v_rfs->push_back(ls_front);
	//Trapezoid
	Function* t_front = new Function("MEDIUM", 250, 350, 550, 650);
	v_rfs->push_back(t_front);
	//Right shoulder
	Function* rs_front = new Function("FAR", 550, 750, 5001, 5001);
	v_rfs->push_back(rs_front);

	Graph* RFS = new Graph("RFS", v_rfs);

	/* Right BACK Sensor */
	vector<Function*>* v_rbs = new vector<Function*>();
	//Left shoulder
	Function* ls_back = new Function("CLOSE", 0, 0, 250, 400);
	v_rbs->push_back(ls_back);
	//Trapezoid
	Function* t_back = new Function("MEDIUM", 250, 350, 550, 650);
	v_rbs->push_back(t_back);
	//Right shoulder
	Function* rs_back = new Function("FAR", 550, 750, 5001, 5001);
	v_rbs->push_back(rs_back);

	Graph* RBS = new Graph("RBS", v_rbs);

	/* LEFT wheel */
	vector<Function*>* v_lw = new vector<Function*>();
	//BACK
	Function* b_left = new Function("BACK", -240, -140, -40, 60);
	v_lw->push_back(b_left);
	//Left shoulder
	Function* ls_left = new Function("SLOW", -54, 0, 72, 144);
	v_lw->push_back(ls_left);
	//Trapezoid
	Function* t_left = new Function("NORMAL", 54, 108, 180, 234);
	v_lw->push_back(t_left);
	//Right shoulder
	Function* rs_left = new Function("FAST", 144, 216, 258, 300);
	v_lw->push_back(rs_left);

	Graph* LW = new Graph("LW", v_lw);

	/* RIGHT wheel */
	vector<Function*>* v_rw = new vector<Function*>();
	//BACK
	Function* b_right = new Function("BACK", -240, -140, -40, 60);
	v_rw->push_back(b_right);
	//Left shoulder
	Function* ls_right = new Function("SLOW", -54, 0, 72, 144);
	v_rw->push_back(ls_right);
	//Trapezoid
	Function* t_right = new Function("NORMAL", 54, 108, 180, 234);
	v_rw->push_back(t_right);
	//Right shoulder
	Function* rs_right = new Function("FAST", 144, 216, 258, 300);
	v_rw->push_back(rs_right);

	Graph* RW = new Graph("RW", v_rw);


	graphs->push_back(RFS);
	graphs->push_back(RBS);
	graphs->push_back(LW);
	graphs->push_back(RW);

	return graphs;
}

vector<Rule*>* FuzzyObstacleAvoidanceTable() {

	/** RULE TABLE CREATION  **/
	vector<Rule*>* table = new vector<Rule*>();

	Rule* r1 = new Rule(1, "CLOSE", "CLOSE", "BACK", "BACK");
	Rule* r2 = new Rule(2, "CLOSE", "MEDIUM", "SLOW", "BACK");
	Rule* r3 = new Rule(3, "CLOSE", "FAR", "NORMAL", "BACK");
	Rule* r4 = new Rule(4, "MEDIUM", "CLOSE", "BACK", "SLOW");
	Rule* r5 = new Rule(5, "MEDIUM", "MEDIUM", "BACK", "NORMAL");
	Rule* r6 = new Rule(6, "MEDIUM", "FAR", "SLOW", "BACK");
	Rule* r7 = new Rule(7, "FAR", "CLOSE", "BACK", "SLOW");
	Rule* r8 = new Rule(8, "FAR", "MEDIUM", "SLOW", "FAST");
	Rule* r9 = new Rule(9, "FAR", "FAR", "FAST", "FAST");

	table->push_back(r1);
	table->push_back(r2);
	table->push_back(r3);
	table->push_back(r4);
	table->push_back(r5);
	table->push_back(r6);
	table->push_back(r7);
	table->push_back(r8);
	table->push_back(r9);

	return table;
}