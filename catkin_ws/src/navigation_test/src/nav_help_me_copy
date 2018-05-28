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
geometry_msgs::Twist vel; //控制机器人速度
std_msgs::String sound_flag; //语音控制标志
std_msgs::String send_flag; 
geometry_msgs::PoseWithCovariance  car_pose;
geometry_msgs::Pose goal_pose;//目标位置

//定义不同房间位置的坐标点
geometry_msgs::Pose kitchen;
geometry_msgs::Pose kitchentable;
geometry_msgs::Pose hallway;
geometry_msgs::Pose littletable;
geometry_msgs::Pose diningroom;
geometry_msgs::Pose livingroom;
geometry_msgs::Pose coffeetable;

ros::Publisher nav_pub;
ros::Publisher cmd_vel_pub;
ros::Publisher return_pub;
ros::Publisher nav_pub_image;

ros::Subscriber emergency2nav_sub;
ros::Subscriber follow_sub;
ros::Subscriber car_sub;    //记住汽车位置
ros::Subscriber move_sub;
ros::Subscriber guide_sub;

void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
void followCallback(const std_msgs::String::ConstPtr& msg);
void guideCallback(const std_msgs::String::ConstPtr& msg);

void initplace()
{
  kitchen.position.x = -0.0482174;
  kitchen.position.y = -0.759977;
  kitchen.position.z = 0;
  kitchen.orientation.x = 0;
  kitchen.orientation.y = 0;
  kitchen.orientation.z = -0.498589;
  kitchen.orientation.w = 0.866839;
  
  kitchentable.position.x = 1.86208;
  kitchentable.position.y = 0.353316;
  kitchentable.position.z = 0;
  kitchentable.orientation.x = 0;
  kitchentable.orientation.y = 0;
  kitchentable.orientation.z = -0.243283;
  kitchentable.orientation.w = 0.969955;

  hallway.position.x = 3.99079;
  hallway.position.y = 1.41218;
  hallway.position.z = 0;
  hallway.orientation.x = 0;
  hallway.orientation.y = 0;
  hallway.orientation.z = -0.465073;
  hallway.orientation.w = 0.885272;

  littletable.position.x = 5.59921;
  littletable.position.y = -2.09411;
  littletable.position.z = 0;
  littletable.orientation.x = 0;
  littletable.orientation.y = 0;
  littletable.orientation.z = -0.46708;
  littletable.orientation.w = 0.884215;
  
  diningroom.position.x = 7.83674;
  diningroom.position.y = -4.56869;
  diningroom.position.z = 0;
  diningroom.orientation.x = 0;
  diningroom.orientation.y = 0;
  diningroom.orientation.z =  -0.475367;
  diningroom.orientation.w =  0.879788;

  livingroom.position.x = 2.90038;
  livingroom.position.y = -5.0066;
  livingroom.position.z = 0;
  livingroom.orientation.x = 0;
  livingroom.orientation.y = 0;
  livingroom.orientation.z =  -0.502187;
  livingroom.orientation.w =  0.864759;

  coffeetable.position.x = 4.38737;
  coffeetable.position.y = -7.93005;
  coffeetable.position.z = 0;
  coffeetable.orientation.x = 0;
  coffeetable.orientation.y = 0;
  coffeetable.orientation.z = -0.492715;
  coffeetable.orientation.w = 0.870191;

}

void turn_robot(float theta)
{
    int count = 0;
    float time = 5;
    ros::Rate loop_rate(10);
    int num = time*10;
    vel.angular.z = theta;    
    count = 0;
    while(count < num)
    {
        count++;
        cmd_vel_pub.publish(vel);
        loop_rate.sleep();
    }
    vel.angular.z = 0.0;
    cmd_vel_pub.publish(vel);
    cout<<"转弯\n";
    sleep(1);
}


//语音控制“stop following me”
void followCallback(const std_msgs::String::ConstPtr& msg)
{
	if(msg->data == "follow_stop")
    {
		ifFollow=false;
	}
}

void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    //在停止follow的情况下，调用该回调函数
    if(ifFollow==false)
    {
		car_pose=msg->pose;//定义此时AMCL中的汽车位置 ,car_pose.pose才是geometry_msgs::Pose类型
		send_flag.data = "grasp";
		nav_pub.publish(send_flag);
		
		cout<<"The robot has followed operator to the car location!"<<endl;
		cout<<"Ready to grasp the bag"<<endl;
		ifFollow=true;
	}	
    
}

//移动到目标点并返回汽车位置的回调函数,从语音话题 voice2bring
void moveCallback(const std_msgs::String::ConstPtr& msg)
{   
	//turn_robot(1.0);
ROS_INFO("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	if(msg->data == "")
	{
		go=false;
	}//如果消息为空，机器人不动

	if(msg->data == "kitchen")
	{
		goal_pose = kitchen;
		go = true;
	}
	if(msg->data == "kitchentable")
	{
		goal_pose = kitchentable;
		go = true;
	}
	if(msg->data == "hallway")
	{
		goal_pose = hallway;
		go = true;
	}
	if(msg->data == "littletable")
	{
		goal_pose = littletable;
		go = true;
	}
	if(msg->data == "diningroom")
	{
		goal_pose = diningroom;
		go = true;
	}
	if(msg->data == "livingroom")
	{
		goal_pose = livingroom;
		go = true;
	}
        if(msg->data == "coffeetable")
	{
		goal_pose = coffeetable;
		go = true;
	}
		    
}
void emergencyCallback(const std_msgs::String::ConstPtr& msg)
{
if(msg->data == "open_door")
{
	std_msgs::String door_flag;
	door_flag.data = "open_door";
	return_pub.publish(door_flag);
}
else
return;
}           
void guideCallback(const std_msgs::String::ConstPtr& msg)
{
    if(msg->data == "instruction_over")
    {
		ifGuide=true;
		//step=3;
	}
}                    
//主函数
int main(int argc, char** argv)
{
	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	initplace();
	cout<<"Welcome to Help-me-carry!"<<endl;

	return_pub= myNode.advertise<std_msgs::String>("nav2speech", 1);
	cmd_vel_pub = myNode.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1); // 急停开关控制turltebot停止的一个话题
	nav_pub = myNode.advertise<std_msgs::String>("/nav2arm", 10);
	nav_pub_image = myNode.advertise<std_msgs::String>("/nav2image", 10);
	ros::Subscriber car_sub = myNode.subscribe("/amcl_pose", 100, carlocationCallback);//订阅amcl包中的amcl_pose话题

	ros::Subscriber follow_sub = myNode.subscribe("/ifFollowme", 1, followCallback);
	ros::Subscriber move_sub = myNode.subscribe("/voice2bring", 1, moveCallback);
	ros::Subscriber guide_sub = myNode.subscribe("/voice2guide", 1, guideCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
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

			//导航反馈直至到达目标点      
			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"Yes! The robot has moved to the goal,ready to realse the grocery!"<<endl;
				send_flag.data = "release";
				nav_pub.publish(send_flag);
				return_pub.publish(send_flag);
                                nav_pub_image.publish(send_flag);
				cout<<"I have sent the release signal to arm!"<<endl;

				go=false;
				//sleep(15);

			}
		
		}
		if(ifGuide==true)
		{
				naviGoal.target_pose.header.frame_id = "map"; 
				naviGoal.target_pose.header.stamp = ros::Time::now();
				naviGoal.target_pose.pose = geometry_msgs::Pose(car_pose.pose);
				while(!mc_.waitForServer(ros::Duration(5.0)))
				{
					//等待服务初始化
					cout<<"Waiting for the server..."<<endl;
				}
				mc_.sendGoal(naviGoal);
				mc_.waitForResult(ros::Duration(60.0));
				if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
				{
					sound_flag.data = "arrived";
					return_pub.publish(sound_flag);
					cout<<"Yes! The robot has come back to the car!"<<endl;
					break;
					go=false;
					ifGuide=false;
				}
		}
		ros::spinOnce();
	}
	return 0;
}
