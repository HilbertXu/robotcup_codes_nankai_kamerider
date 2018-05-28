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
#include <kobuki_msgs/DigitalInputEvent.h>
#include <kobuki_msgs/ButtonEvent.h>
//move_base头文件
#include<move_base_msgs/MoveBaseGoal.h>
#include<move_base_msgs/MoveBaseAction.h>
//actionlib头文件
#include<actionlib/client/simple_action_client.h>
#include <stdlib.h>
#include<cstdlib>
using namespace std;
//定义的全局变量
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; //简化类型书写为MoveBaseClient
int step=0;
int num=0;
int ifStopGetPoint=0;
//定义不同房间位置的坐标点
geometry_msgs::PoseWithCovariance  car_pose;
geometry_msgs::PoseWithCovariance  table;
geometry_msgs::Pose Order_position1;
geometry_msgs::Pose Bar_position;
ros::Subscriber car_sub;
ros::Publisher nav2img_pub;
ros::Subscriber move_sub;
ros::Subscriber speech_sub;
ros::Subscriber table_sub;
ros::Publisher nav2speech_pub;
void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
void speechCallback(const std_msgs::String::ConstPtr& msg)
{

  if(msg->data == "return")
  {
	 step = 3;
  }
  if(msg->data == "start")
  {
num=4;
	 step = 2;
  }
  if(msg->data == "go-back")
  {
	 step =4 ;
  }
}
void atTableback(const std_msgs::String::ConstPtr& msg)
{

  if(msg->data == "found_table")
  {
	 ifStopGetPoint=1;
  }
}

//主函数
int main(int argc, char** argv)
{
	//set pose
	//people
  //Order_position1.position.x = 6.33525;
  //Order_position1.position.y = -1.87814;
  //Order_position1.position.z = 0;
  //Order_position1.orientation.x = 0;
  //Order_position1.orientation.y = 0;
  //Order_position1.orientation.z = -0.798706;
  //Order_position1.orientation.w =  0.601721;

	//living_room
	//Bar_position.position.x = 0.0548753;
	//Bar_position.position.y = 1.07494;
	//Bar_position.position.z = 0;
	//Bar_position.orientation.x = 0;
	//Bar_position.orientation.y = 0;
	//Bar_position.orientation.z = 0.863549;
	//Bar_position.orientation.w = 0.504265;
	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	cout<<"Welcome to restaurant!"<<endl;

	nav2img_pub= myNode.advertise<std_msgs::String>("/nav2img", 1);
	nav2speech_pub= myNode.advertise<std_msgs::String>("/nav2speech", 1);
	ros::Subscriber car_sub = myNode.subscribe("/amcl_pose", 100, carlocationCallback);//订阅amcl包中的amcl_pose话题
	//ros::Subscriber move_sub = myNode.subscribe("/doorstate", 1, moveCallback);
	ros::Subscriber speech_sub = myNode.subscribe("/speech2nav", 1, speechCallback);
        ros::Subscriber table_sub = myNode.subscribe("/at_table", 1, atTableback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端


	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
		ROS_INFO("INTO THE MAIN");
		if(step==2)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(table.pose);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach Order_position1"<<endl;
				std_msgs::String str;
				str.data = "wave";
				nav2speech_pub.publish(str);
			}

			step = 1;
		}
		if(step==3)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(car_pose.pose);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach Order_position1"<<endl;
				std_msgs::String str;
				str.data = "arrived_bar_position";
				nav2speech_pub.publish(str);
			}

			step = 1;
		}
                if(step==4)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(table.pose);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach Order_position1"<<endl;
				std_msgs::String str;
				str.data = "arrived_customer_position";
				nav2speech_pub.publish(str);
			}

			step = 1;
		}
		ros::spinOnce();
	}
	return 0;
}
void carlocationCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{if(num==0)
	{car_pose=msg->pose;//定义此时AMCL中的汽车位置 ,car_pose.pose才是geometry_msgs::Pose类型
num=2;}
if(num==4)
{table=msg->pose;
num=2;
}
if(ifStopGetPoint==0){
table=msg->pose;
}
}
