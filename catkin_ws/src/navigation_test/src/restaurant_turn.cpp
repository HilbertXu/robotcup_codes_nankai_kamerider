#include <ros/ros.h>
#include <std_msgs/String.h>
#include<geometry_msgs/Twist.h>
#include <signal.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <string.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <cmath>
class TurnLeft
{
public:
  ros::NodeHandle nh;
  ros::Publisher turn_pub;//to image
  ros::Publisher cmd_vel_pub;
  ros::Subscriber sound_sub;
  TurnLeft(ros::NodeHandle &nh):nh(nh){}
  ~TurnLeft(){}

  void init()
  {
    turn_pub = nh.advertise<std_msgs::String>("/turnleft",1);
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi",1);
    sound_sub = nh.subscribe("/speech2nav", 1, &TurnLeft::soundCallback,this);
  }

  void turn_robot(float theta, float time)
  {
    int count = 0;
    //float time = 3;
    ros::Rate loop_rate(10);
    int num = time*10;
    geometry_msgs::Twist vel;
    vel.angular.z = theta/time;
    count = 0;
    while(count < num)
      {
        count++;
        cmd_vel_pub.publish(vel);
        loop_rate.sleep();
      }
    vel.angular.z = 0.0;
    cmd_vel_pub.publish(vel);
    sleep(1);
  }

  void turn_left()
  {
    //TurnLeft::turn_robot(2.62,2.5);
    TurnLeft::turn_robot(3,2.5);
    std_msgs::String str;
    turn_pub.publish(str);
  }

  void detectaround()
  {
    for(int i = 0; i < 4; ++i)
      {
        TurnLeft::turn_left();
      }
  }
  void soundCallback(const std_msgs::String::ConstPtr& msg)
  {
	  if(msg->data == "start")
	  {
		TurnLeft::detectaround();
	  }
  }
};

int main (int argc, char** argv)
{
	ros::init (argc, argv, "restaurant_turn");
	ros::NodeHandle nh("~");
	TurnLeft tl(nh);
	tl.init();
	ros::spin ();
	exit(0);
	return 0;
}
