#include "stdafx.h"
#include "FL_.h"

void FuzzyRightEdgeController() {

	/** SENSORS CONFIGURATION **/
	int sonar_range[NUM_SENSORS];
	ArSensorReading *sonar_sensor[NUM_SENSORS];
	double left_wheel = 0.0, right_wheel = 0.0;

	/** FUZZY LOGIC CONFIGURATION **/
	vector<Graph*>* graphs = FuzzyRightEdgeGraphs();
	vector<Rule*>* table = FuzzyRightEdgeTable();

	FuzzyLogic* fuzzy = new FuzzyLogic(graphs, table);

	while (true) {
		/* Recollection of the sonar distances */
		for (int i = 0; i < NUM_SENSORS; i++) {
			sonar_sensor[i] = robot->getSonarReading(i);
			sonar_range[i] = sonar_sensor[i]->getRange();
		}

		//FOR THE REAL ROBOT
		/*if (sonar_range[6] > 800) {
			sonar_range[6] = 400;
			
		} 
		if (sonar_range[7] > 800) {
			sonar_range[7] = 799;
			sonar_range[6] = 799;

		}*/

		/* Calculation of the wheel motor speed using Fuzzy Logic */
		vector<double> speed = fuzzy->FuzzyLogicAlgorithm(sonar_range[6], sonar_range[7]);
		left_wheel = speed[0];
		right_wheel = speed[1];

		/* Seting up velocity to the robot's wheels */
		cout << "SENSOR-6: " << sonar_range[6] << " - SENSOR-7: " << sonar_range[7] << endl;
		cout << "LEFT: " << left_wheel << " - RIGHT: " << right_wheel << endl;
		robot->setVel2(left_wheel, right_wheel);
	}
}

vector<Graph*>* FuzzyRightEdgeGraphs() {

	/** GRAPH CREATION  **/
	vector<Graph*>* graphs = new vector<Graph*>();


	/* Right FRONT Sensor */
	vector<Function*>* v_rfs = new vector<Function*>();
	//Left shoulder
	Function* ls_front = new Function("CLOSE", 0, 0, 250, 3800); 
	v_rfs->push_back(ls_front);
	//Trapezoid
	Function* t_front = new Function("MEDIUM", 150, 350, 550, 750); 
	v_rfs->push_back(t_front);
	//Right shoulder
	Function* rs_front = new Function("FAR", 50, 650, 5001, 5001);
	v_rfs->push_back(rs_front);

	Graph* RFS = new Graph("RFS", v_rfs);

	/* Right BACK Sensor */
	vector<Function*>* v_rbs = new vector<Function*>();
	//Left shoulder
	Function* ls_back = new Function("CLOSE", 0, 0, 250, 3800); 
	v_rbs->push_back(ls_back);
	//Trapezoid
	Function* t_back = new Function("MEDIUM", 150, 350, 550, 750); 
	v_rbs->push_back(t_back);
	//Right shoulder
	Function* rs_back = new Function("FAR", 50, 650, 5001, 5001);
	v_rbs->push_back(rs_back);

	Graph* RBS = new Graph("RBS", v_rbs);

	/* LEFT wheel */
	vector<Function*>* v_lw = new vector<Function*>();
	//Left shoulder
	Function* ls_left = new Function("SLOW", 0, 0, 72, 144);
	v_lw->push_back(ls_left);
	//Trapezoid
	Function* t_left = new Function("NORMAL", 54, 108, 180, 234); 
	v_lw->push_back(t_left);
	//Right shoulder
	Function* rs_left = new Function("FAST", 144, 216, 288, 288);
	v_lw->push_back(rs_left);

	Graph* LW = new Graph("LW", v_lw);

	/* RIGHT wheel */
	vector<Function*>* v_rw = new vector<Function*>();
	//Left shoulder
	Function* ls_right = new Function("SLOW", 0, 0, 72, 144);
	v_rw->push_back(ls_right);
	//Trapezoid
	Function* t_right = new Function("NORMAL", 54, 108, 180, 234);
	v_rw->push_back(t_right);
	//Right shoulder
	Function* rs_right = new Function("FAST", 144, 216, 288, 288);
	v_rw->push_back(rs_right);

	Graph* RW = new Graph("RW", v_rw);

	graphs->push_back(RFS);
	graphs->push_back(RBS);
	graphs->push_back(LW);
	graphs->push_back(RW);

	return graphs;
}

vector<Rule*>* FuzzyRightEdgeTable() {

	/** RULE TABLE CREATION  **/
	vector<Rule*>* table = new vector<Rule*>();

	Rule* r1 = new Rule(1, "CLOSE", "CLOSE", "SLOW", "FAST");
	Rule* r2 = new Rule(2, "CLOSE", "MEDIUM", "SLOW", "NORMAL");
	Rule* r3 = new Rule(3, "CLOSE", "FAR", "SLOW", "FAST");
	Rule* r4 = new Rule(4, "MEDIUM", "CLOSE", "SLOW", "NORMAL"); 
	Rule* r5 = new Rule(5, "MEDIUM", "MEDIUM", "NORMAL", "NORMAL");
	Rule* r6 = new Rule(6, "MEDIUM", "FAR", "NORMAL", "SLOW"); 
	Rule* r7 = new Rule(7, "FAR", "CLOSE", "FAST", "SLOW");
	Rule* r8 = new Rule(8, "FAR", "MEDIUM", "NORMAL", "SLOW");
	Rule* r9 = new Rule(9, "FAR", "FAR", "FAST", "SLOW");

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