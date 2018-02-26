# Fuzzy-Logic-Controller
System that allows a Pioneer robot to perform Right Edge Following and Obstacle Avoidance behaviors implementing Fuzzy Logic and PID Controllers.

The structure of the system can be seen in the [` FL_classdiagram.png `](./FL_classdiagram.png) image.

Basically, this project has 4 different parts in which in all of them the robot performs right an edge following or similar behavior. 
The part that connects the robot with the system is the same in all of them and it is as follows:

#### Connection with the robot
```
Aria::init();
	ArPose pose;
	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();
	ArRobotConnector robotConnector(&argParser, robot);
	if (robotConnector.connectRobot())
		cout << "Robot Connected! --------------------- :)" << endl;
	ROBOTconfiguration();
 
```

```
void ROBOTconfiguration() {
	/**/
	robot->runAsync(false);
	robot->lock();
	robot->enableMotors();
	robot->unlock();
}

```
It is advisable to disconnect the robot at the end of the execution

```
void ROBOTshutdown() {
	robot->lock();
	robot->stop();
	robot->unlock();
	Aria::exit();
}

```

## PID Controller

```
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
```

## Fuzzy Logic / Right Edge Following

In order to define the Rule Tables and Membership Function Graphs. It should be modifies the ` FuzzyRightEdgeGraphs() `  and ` FuzzyRightEdgeTable ` methods from the **FL_RightEdgeFollowing.cpp** file.

In addition, these are the chosen Membership Funcions: [` Distance_REF.png `](./Graphs/distance_REF.png) and  [` Speed_REF.png `](./Graphs/Speed_REF.png), and this is the final Rule Table [` Table_REF.png `](./Graphs/Table_REF.png).


## Fuzzy Logic / Obstacle Avoidance

In order to define the Rule Table and Membership Function Graphs. It should be modify the ` FuzzyRightEdgeGraphs() `  and ` FuzzyRightEdgeTable ` methods from the **FL_ObstacleAvoidance.cpp** file.

In addition, these are the chosen Membership Funcions: [` Distance_OA.png `](./Graphs/Distance_OA.png) and  [` Speed_OA.png `](./Graphs/Speed_OA.png), and this is the final Rule Table [` Table_OA.png `](./Graphs/Table_OA.png).

## Fuzzy Logic / Right Edge Following and Obstacle Avoidance

The integration of both Logics has been done in a very simple way. 

` /** ACTIVATION OF OBSTACLE AVOIDANCE **/
		if (min_f < 250) `
    
