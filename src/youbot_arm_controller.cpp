#include <ros/ros.h>
#include <ros/console.h>
#include <brics_actuator/JointPositions.h>
#include <string>
#include <iostream>
#include "YoubotArmController.h"
using namespace std;
using namespace ros;


	YoubotArmController::YoubotArmController()
	{
		YoubotArmController::position_publisher = YoubotArmController::nh.advertise<brics_actuator::JointPositions>("arm_1/arm_controller/position_command",1);
	}
	YoubotArmController::~YoubotArmController(){}
	
	void YoubotArmController::publishjointposition(std::vector<double> jointangles)
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
		YoubotArmController::position_publisher.publish(jointpositions);
	  }

