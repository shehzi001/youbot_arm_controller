#include <ros/ros.h>
#include <ros/console.h>
#include <brics_actuator/JointPositions.h>
#include <string>
#include <iostream>

#include "YoubotArmController.h"
using namespace std;
using namespace ros;
/*
class RobotArmController {
public:
	RobotArmController()
	{
		position_publisher = nh.advertise<brics_actuator::JointPositions>("arm_1/arm_controller/position_command",1);
	}
	~RobotArmController(){}
	
	void publishjointposition(std::vector<double> jointangles)
	  { 
		brics_actuator::JointPositions jointpositions;
		jointpositions.positions.resize(jointangles.size());
		
		for (int i = 0;i < jointangles.size();i++)
		{	std::stringstream jointname;
			jointname.str("");
			jointname << "arm_joint_" << (i + 1);
			jointpositions.positions[i].joint_uri = jointname.str();
			jointpositions.positions[i].unit = "rad";
			jointpositions.positions[i].value = jointangles[i];
		}
		position_publisher.publish(jointpositions);
	  }
private:
	ros::NodeHandle nh;
	ros::Publisher position_publisher;
	
};
*/
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
		cout << "Select mode for Arm Position setting:Home(h),Candle(c) or Manual Setting(m)" << endl;
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
			else
				{
					cout << endl << "\nWrong mode selected." <<  endl;
					break;
				}			
		rate.sleep();
	}
	
	return 0;
}
