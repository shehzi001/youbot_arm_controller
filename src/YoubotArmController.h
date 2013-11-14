
#ifndef YOUBOT_ARM_CONTROLLER_H_
#define YOUOT_ARM_CONTROLLER_H_
class YoubotArmController {
public:
	YoubotArmController();
	~YoubotArmController();
	void publishjointposition(std::vector<double> jointangles);
private:
	ros::NodeHandle nh;
	ros::Publisher position_publisher;
};
#endif
