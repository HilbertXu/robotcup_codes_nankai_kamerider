#include <ros/ros.h>
#include <std_msgs/String.h>
#include <kobuki_msgs/MotorPower.h>
#include <string.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <kobuki_msgs/DigitalInputEvent.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <cmath>
const double pi = 3.141592653;
using namespace std;
bool estop_in0;
bool estop_in1;
bool estop_in2;
ros::Subscriber emergency_sub;
ros::Publisher motor_power_pub;
ros::Publisher move_base_cancel_pub;
ros::Publisher emergency2speech_pub;
void DigitalInputEventCallback(const kobuki_msgs::DigitalInputEvent::ConstPtr& msg)
{
	ROS_INFO("DigitalInputEventCallback");
	estop_in0 = msg->values[0];
	estop_in1 = msg->values[1];
	estop_in2 = msg->values[2];
	if(estop_in2)
	{
		ROS_INFO("**************************");
		kobuki_msgs::MotorPower offcmd;
		offcmd.state = kobuki_msgs::MotorPower::OFF;
		motor_power_pub.publish(offcmd);
		actionlib_msgs::GoalID cancelcmd;
		move_base_cancel_pub.publish(cancelcmd);
	}
	if(estop_in0||estop_in1)
	{
		std_msgs::String switch_state;
		switch_state.data = "true";
		emergency2speech_pub.publish(switch_state);
	}
	else
	{
		std_msgs::String switch_state;
		switch_state.data = "false";
		emergency2speech_pub.publish(switch_state);
	}
}

int main (int argc, char** argv)
{
  ros::init (argc, argv, "emergency");
  ros::NodeHandle nh;
  emergency_sub = nh.subscribe("/mobile_base/events/digital_input", 1, DigitalInputEventCallback);
  motor_power_pub = nh.advertise<kobuki_msgs::MotorPower>("/mobile_base/commands/motor_power", 1);
  move_base_cancel_pub = nh.advertise<actionlib_msgs::GoalID>("move_base/cancel",1);
  emergency2speech_pub = nh.advertise<std_msgs::String>("/emergency2speech",10);
  estop_in2 = 0;
  ros::spin();
  return 0;
}
