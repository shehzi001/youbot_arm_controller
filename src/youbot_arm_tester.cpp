#include <ros/ros.h>
#include <ros/console.h>
#include <brics_actuator/JointPositions.h>
#include <string>
#include <iostream>

#include "YoubotArmController.h"
using namespace std;
using namespace ros;

int main(int argc,char **argv){
	
	ros::init(argc, argv,"robot_arm_controller");
	ros::NodeHandle nh;
	ros::Rate rate(10);
	YoubotArmController rac;
	int numberofjoints = 5;
	
	static const double candle[] = { 2.9, 1.1, -2.5, 1.7, 1.5};
	std::vector<double> joint_angles_candle (candle, candle + sizeof(candle) / sizeof(candle[0]) );
	
	static const double home[] = { 0.02, 0.02, -0.02, 0.03, 0.12};
	std::vector<double> joint_angles_home (home, home + sizeof(home) / sizeof(home[0]) );

	char mode;
	//rate.sleep();
	while(nh.ok())
	 {	
		cout << "\nSelect mode for Arm Position setting:Home(h),Candle(c),Manual Input(m) or Exit(e)" << endl;
		cin >> mode;	
			if (mode == 'h')
				{
					rac.publishjointposition(joint_angles_home);
				}
			else if (mode == 'c')
				{
					rac.publishjointposition(joint_angles_candle);
				}
			else if (mode == 'm')
				{ 	std::vector<double> angles(5);
					for (int i = 0;i < numberofjoints;i++)
					{	cout << "\nJoint " << (i+1) << " Angle : ";
						cin >> angles[i];
					}
					rac.publishjointposition(angles);
				}
			else if(mode == 'e')
				{
					cout << endl << "\nTerminating..." <<  endl;
					break;
				}		
			else 
					cout << endl << "\nInvalid Input..." <<  endl;
		rate.sleep();
	}
	
	return 0;
}
