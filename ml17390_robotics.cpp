// ml17390_robotics.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "PID.h"
#include "FL_.h"

ArRobot* robot = new ArRobot();
/** ROBOT CONFIGURATIONS **/
void ROBOTconfiguration();
void ROBOTshutdown();


int main(int argc, char **argv) {

	/* ROBOT CONNECTION */
	Aria::init();
	ArPose pose;
	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();
	ArRobotConnector robotConnector(&argParser, robot);
	if (robotConnector.connectRobot())
		cout << "Robot Connected! --------------------- :)" << endl;
	ROBOTconfiguration();

	/* LASERS *
	argParser.addDefaultArgument("-connectLaser");
	ArLaserConnector laserConnector(&argParser, robot, &robotConnector);
	if (laserConnector.connectLasers())
		cout << "Laser Connected!----------------------@@@@@@@@@@@@@@@@@@@@@@" << endl;*/


	int option = 0;
	do {
		/* MENU TO CHOOSE THE PLAY MODE */
		cout << "PLEASE, CHOOSE ONE OF THE FOLLOWING:" << endl;
		cout << "1) - PID Controller Right Edge Following Behaviour" << endl;
		cout << "2) - Fuzzy Logic Control Right Edge Following Behaviour" << endl;
		cout << "3) - Fuzzy Logic Control Obstacle Avoidance Behaviour" << endl;
		cout << "4) - Fuzzy Logic Control Right Edge Following and Obstacle Avoidance Behaviours" << endl;
		cin >> option;
		switch (option) {
		case 1:
			cout << "Running option:" << endl;
			cout << "1) - PID Controller Right Edge Following Behaviour" << endl;
			PIDcontroller();
			break;
		case 2:
			cout << "Running option:" << endl;
			cout << "2) - Fuzzy Logic Control Right Edge Following Behaviour" << endl;
			FuzzyRightEdgeController();
			break;
		case 3:
			cout << "Running option:" << endl;
			cout << "3) - Fuzzy Logic Control Obstacle Avoidance Behaviour" << endl;
			FuzzyObstacleAvoidanceController();
			break;
		case 4:
			cout << "Running option:" << endl;
			cout << "4) - Fuzzy Logic Control Right Edge Following and Obstacle Avoidance Behaviours" << endl;
			FuzzyBoth();
			break;
		default:
			cout << "INCORRECT NUMBER, please introduce a valid input!" << endl;
			break;
		}
	} while (option != 1 && option != 2 && option != 3 && option != 4);

	/* ROBOT SHUTTING DOWN */
	ROBOTshutdown();
	
	return 0;
}

void ROBOTconfiguration() {
	/**/
	robot->runAsync(false);
	robot->lock();
	robot->enableMotors();
	robot->unlock();
}
void ROBOTshutdown() {
	robot->lock();
	robot->stop();
	robot->unlock();
	Aria::exit();
}