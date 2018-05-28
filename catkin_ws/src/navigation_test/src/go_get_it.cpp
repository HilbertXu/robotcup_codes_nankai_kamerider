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
bool back = false;
bool ifFollow=true;    // 是否在跟人
bool iflearn=false;    // 是否在学新地点
bool bcarry=true;
int car_num=0;
geometry_msgs::Twist vel; //控制机器人速度
std_msgs::String sound_flag; //语音控制标志
std_msgs::String send_flag; 
geometry_msgs::PoseWithCovariance  car_pose[5];
geometry_msgs::PoseWithCovariance  start_pose;
geometry_msgs::PoseWithCovariance goal_pose;//目标位置

//ros::Publisher nav_pub;
ros::Publisher cmd_vel_pub;
ros::Publisher return_pub;
//ros::Publisher nav_pub_image;

ros::Subscriber emergency2nav_sub;
ros::Subscriber follow_sub;
ros::Subscriber car_sub;    //记住汽车1位置
ros::Subscriber move_sub;
ros::Subscriber guide_sub;

void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
void followCallback(const std_msgs::String::ConstPtr& msg);


//语音控制“stop following me”
void followCallback(const std_msgs::String::ConstPtr& msg)
{
	if(msg->data == "follow_stop")
    {
		ifFollow=false;
	}
	if(msg->data == "bed")
    {
		iflearn=true;
	}
	if(msg->data == "side-shelf")
    {
		iflearn=true;
	}
	if(msg->data == "teepee")
    {
		iflearn=true;
	}
	if(msg->data == "desk")
    {
		iflearn=true;
	}
	if(msg->data == "book-shelf")
    {
		iflearn=true;
	}
}

void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    //在停止follow的情况下，调用该回调函数
    if(ifFollow==false)
    {
		start_pose=msg->pose;//定义此时AMCL中的汽车位置 ,car_pose.pose才是geometry_msgs::Pose类型
		send_flag.data = "arrive_startpoint";
		return_pub.publish(send_flag);
		cout<<"The robot has followed operator to the start location!"<<endl;
		ifFollow=true;
	}	
    if(iflearn==true)
    {
		car_pose[car_num]=msg->pose;//定义此时AMCL中的汽车位置 ,car_pose.pose才是geometry_msgs::Pose类型
		send_flag.data = "remember";
		return_pub.publish(send_flag);
		car_num++;
		iflearn=false;
	}	    
}

//移动到目标点并返回汽车位置的回调函数,从语音话题 voice2bring
void moveCallback(const std_msgs::String::ConstPtr& msg)
{   
	if(msg->data == "")
	{
		go=false;
	}//如果消息为空，机器人不动

	if(msg->data == "1")
	{
		goal_pose = car_pose[0];
		go = true;
	}
	if(msg->data == "2")
	{
		goal_pose = car_pose[1];
		go = true;
	}
	if(msg->data == "3")
	{
		goal_pose = car_pose[2];
		go = true;
	}
	if(msg->data == "4")
	{
		goal_pose = car_pose[3];
		go = true;
	}
	if(msg->data == "5")
	{
		goal_pose = car_pose[4];
		go = true;
	}
	if(msg->data == "start_point")
	{
		goal_pose = start_pose;
		back = true;
	}	    
}                             
//主函数
int main(int argc, char** argv)
{
	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	cout<<"Welcome to go-get-it!"<<endl;

	return_pub= myNode.advertise<std_msgs::String>("nav2speech", 1);
	cmd_vel_pub = myNode.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1); // 急停开关控制turltebot停止的一个话题
	//nav_pub = myNode.advertise<std_msgs::String>("/nav2arm", 10);
	//nav_pub_image = myNode.advertise<std_msgs::String>("/nav2image", 10);
	ros::Subscriber car_sub = myNode.subscribe("/amcl_pose", 100, carlocationCallback);//订阅amcl包中的amcl_pose话题

	ros::Subscriber follow_sub = myNode.subscribe("/ifFollowme", 1, followCallback);
	ros::Subscriber move_sub = myNode.subscribe("/voice2bring", 1, moveCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点

	while(ros::ok())
	{
		if((go==true))
		{
			//naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(goal_pose.pose);

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
				cout<<"Yes! The robot has moved to the goal"<<endl;
				send_flag.data = "findsomething";
				//nav_pub.publish(send_flag);
				return_pub.publish(send_flag);
	                        //nav_pub_image.publish(send_flag);
				cout<<"I have sent the release signal to arm!"<<endl;

				go=false;
			}
		
		}
		if((back==true))
		{
			//naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.frame_id = "map"; 
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(start_pose.pose);

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
				cout<<"Yes! The robot has moved to the start"<<endl;
				send_flag.data = "next_turn";
				return_pub.publish(send_flag);
				back=false;
			}
		
		}
		ros::spinOnce();
	}
	return 0;
}
