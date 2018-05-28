/***********************************************************
Author: Zheng Haosi
Date: 3/30/2017
Abstract: Code for Help-me-carry task 
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
bool ifFollow=true;    // 是否在跟人
bool bcarry=true;
bool ifGuide=false;   //是否开始引导人
int step=0;
geometry_msgs::Twist vel; //控制机器人速度
std_msgs::String sound_flag; //语音控制标志
std_msgs::String send_flag; 
geometry_msgs::PoseWithCovariance  car_pose;
geometry_msgs::Pose goal_pose;//目标位置

//定义不同房间位置的坐标点
geometry_msgs::Pose livingroom;
geometry_msgs::Pose kitchen;
geometry_msgs::Pose bartable;
geometry_msgs::Pose entrance;
geometry_msgs::Pose balcony;
geometry_msgs::Pose start;
geometry_msgs::Pose exit11;

ros::Publisher nav_pub;
ros::Publisher cmd_vel_pub;
ros::Publisher return_pub;
ros::Publisher nav_pub_image;

ros::Subscriber follow_sub;
ros::Subscriber car_sub;    //记住汽车位置
ros::Subscriber move_sub;
ros::Subscriber guide_sub;
bool switch_state=0;

void followCallback(const std_msgs::String::ConstPtr& msg);
void guideCallback(const std_msgs::String::ConstPtr& msg);

void initplace()
{
//1
  start.position.x =  12.8627;
  start.position.y = 1.14987;
  start.position.z = 0;
  start.orientation.x = 0;
  start.orientation.y = 0;
  start.orientation.z = 0.662806;
  start.orientation.w = 0.748791;

  
  exit11.position.x = 0.0654283;
  exit11.position.y = 1.06126;
  exit11.position.z = 0;
  exit11.orientation.x = 0;
  exit11.orientation.y = 0;
  exit11.orientation.z = 0.859506;
  exit11.orientation.w = 0.511125;
  //2
  livingroom.position.x = 8.57897;
  livingroom.position.y = 3.25528;
  livingroom.position.z = 0;
  livingroom.orientation.x = 0;
  livingroom.orientation.y = 0;
  livingroom.orientation.z =  -0.0857846;
  livingroom.orientation.w =  0.996314;
//3
  kitchen.position.x = 11.9463;
  kitchen.position.y = 2.81379;
  kitchen.position.z = 0;
  kitchen.orientation.x = 0;
  kitchen.orientation.y = 0;
  kitchen.orientation.z = -0.113013;
  kitchen.orientation.w = 0.993593;

  bartable.position.x = 8.51342;
  bartable.position.y = -6.43248;
  bartable.position.z = 0;
  bartable.orientation.x = 0;
  bartable.orientation.y = 0;
  bartable.orientation.z = 0.277456;
  bartable.orientation.w = 0.960738;
//4
  entrance.position.x = 10.3498;
  entrance.position.y = 4.37952;
  entrance.position.z = 0;
  entrance.orientation.x = 0;
  entrance.orientation.y = 0;
  entrance.orientation.z = 0.735302;
  entrance.orientation.w = 0.67774;

  balcony.position.x = 2.98617397856;
  balcony.position.y = -1.49467780406;
  balcony.position.z = 0;
  balcony.orientation.x = 0;
  balcony.orientation.y = 0;
  balcony.orientation.z = 0.492294159753;
  balcony.orientation.w = 0.870428894438;
}

//移动到目标点并返回汽车位置的回调函数,从语音话题 voice2bring
void moveCallback(const std_msgs::String::ConstPtr& msg)
{   

	if(msg->data == "coffee-table")
	{
		goal_pose = livingroom;
		go = true;
	}
	if(msg->data == "kitchen-table")
	{
		goal_pose = kitchen;
		go = true;
	}
	if(msg->data == "bar-table")
	{
		goal_pose = bartable;
		go = true;
	}
	if(msg->data == "kitchen-room")
	{
		goal_pose = bartable;
		go = true;
	}
	if(msg->data == "exit11")
	{
		goal_pose =exit11;
		go = true;
	}		    
}    
void speechCallback(const std_msgs::String::ConstPtr& msg)
{

if(msg->data == "false")
{
        ROS_INFO("switch_get");
	switch_state=true;
}
}         
//主函数
int main(int argc, char** argv)
{
	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	initplace();
	cout<<"Welcome to Help-me-carry!"<<endl;
	ros::Subscriber speech_sub = myNode.subscribe("go_out", 1, speechCallback);
	return_pub= myNode.advertise<std_msgs::String>("/nav2speech", 1);
	cmd_vel_pub = myNode.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1); // 急停开关控制turltebot停止的一个话题
	nav_pub_image = myNode.advertise<std_msgs::String>("/nav2image", 10);

	ros::Subscriber move_sub = myNode.subscribe("/speech2nav", 1, moveCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
		if(step==0&&switch_state==true)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(start);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach viewpoint"<<endl;
				std_msgs::String str;
				str.data = "get_pose";
				return_pub.publish(str);
			}

			step = 1;
		}
		if((go==true))
		{
ROS_INFO("****************************************");
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
			send_flag.data="arrived";
			//导航反馈直至到达目标点      
			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"Yes! The robot has moved to the goal,ready to realse the grocery!"<<endl;
				cout<<"I have sent the release signal to arm!"<<endl;
				go=false;
				//sleep(15);

			}
			sleep(15);
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(start);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach viewpoint"<<endl;
				std_msgs::String str;
				str.data = "arrived";
				return_pub.publish(str);
			}
		
		}

		ros::spinOnce();
	}
	return 0;
}
