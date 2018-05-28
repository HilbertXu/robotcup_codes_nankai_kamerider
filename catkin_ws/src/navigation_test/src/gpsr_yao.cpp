/***********************************************************
Author: yao zonghai
Date: 4/21/2018
Abstract: Code for gpsr_2018_Japanese task 
************************************************************/
//标准头文件
#include<ros/ros.h>
#include<iostream>
#include<std_msgs/String.h>
#include<string.h>
//navigation中需要使用的位姿信息头文件
#include<geometry_msgs/Pose.h>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/PoseWithCovariance.h>
#include<geometry_msgs/PoseWithCovarianceStamped.h>
#include<geometry_msgs/Twist.h>
#include<geometry_msgs/Quaternion.h>
//move_base头文件
#include<move_base_msgs/MoveBaseGoal.h>
#include<move_base_msgs/MoveBaseAction.h>
//actionlib头文件
#include<actionlib/client/simple_action_client.h>
#include<stdlib.h>
#include<cstdlib>

using namespace std;
//定义的全局变量
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; //简化类型书写为MoveBaseClient
bool go = false;
geometry_msgs::Twist vel; //控制机器人速度
std_msgs::String send_flag; 
geometry_msgs::Pose goal_pose;//目标位置

//定义不同房间位置的坐标点
geometry_msgs::Pose livingroom;
geometry_msgs::Pose kitchen;
geometry_msgs::Pose bedroom;
geometry_msgs::Pose out;
geometry_msgs::Pose start;
geometry_msgs::Pose corridor;

ros::Publisher cmd_vel_pub;
ros::Publisher backfeedback_move_pub;
ros::Publisher nav_pub_image;

ros::Subscriber move_sub;


void initplace()
{
  start.position.x = -2.4418;
  start.position.y = -0.5192764;
  start.position.z = 0;
  start.orientation.x = 0;
  start.orientation.y = 0;
  start.orientation.z = 0.607656;
  start.orientation.w = 0.7942;
  

//4

  kitchen.position.x = 8.64592;
  kitchen.position.y = -0.50741;
  kitchen.position.z = 0;
  kitchen.orientation.x = 0;
  kitchen.orientation.y = 0;
  kitchen.orientation.z = -0.729102;
  kitchen.orientation.w = 0.684405;

//7
  livingroom.position.x = 4.79373;
  livingroom.position.y = -6.13591;
  livingroom.position.z = 0;
  livingroom.orientation.x = 0;
  livingroom.orientation.y = 0;
  livingroom.orientation.z = 0.702807;
  livingroom.orientation.w = 0.71138;


//8
  out.position.x = 9.99888;
  out.position.y = -7.92497;
  out.position.z = 0;
  out.orientation.x = 0;
  out.orientation.y = 0;
  out.orientation.z = 0.0977258;
  out.orientation.w = 0.995213;

//9
  bedroom.position.x = -1.69507;
  bedroom.position.y = -0.0639506;
  bedroom.position.z = 0;
  bedroom.orientation.x = 0;
  bedroom.orientation.y = 0;
  bedroom.orientation.z = -0.114929;
  bedroom.orientation.w = 0.993374;

}


void moveCallback(const std_msgs::String::ConstPtr& msg)
{   
	if(msg->data == "")
	{
		go=false;
	}//如果消息为空，机器人不动
        if(msg->data == "start")
	{
		goal_pose = start;
		go = true;
	}
	if(msg->data == "livingroom")
	{
        	goal_pose = livingroom;
		go = true;
	}
	if(msg->data == "kitchen")
	{
		goal_pose = kitchen;
		go = true;
	}
	if(msg->data == "bedroom")
	{
		goal_pose = bedroom;
		go = true;
	}
	
        if(msg->data == "out")
	{
		goal_pose = out;
		go = true;
	}
		    
}  
          
//主函数
int main(int argc, char** argv)
{
	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	initplace();
	cout<<"Welcome to gpsr_yao!"<<endl;

	backfeedback_move_pub= myNode.advertise<std_msgs::String>("/arriveLocation", 1);
	cmd_vel_pub = myNode.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1); // 急停开关控制turltebot停止的一个话题
	//nav_pub = myNode.advertise<std_msgs::String>("/nav2arm", 10);
	//nav_pub_image = myNode.advertise<std_msgs::String>("/nav2image", 10);

	ros::Subscriber move_sub = myNode.subscribe("/speechGiveLocation", 1, moveCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
		if((go==true))
		{
			//naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(goal_pose);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;
			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			//导航反馈直至到达目标点      
			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"Yes! The robot has moved to the goal,ready to do the next step!"<<endl;
				send_flag.data = "arrive_target_place";
				//nav_pub.publish(send_flag);
				backfeedback_move_pub.publish(send_flag);
                                //nav_pub_image.publish(send_flag);

				go=false;
				//sleep(15);

			}
		
		}
		ros::spinOnce();
	}
	return 0;
}
