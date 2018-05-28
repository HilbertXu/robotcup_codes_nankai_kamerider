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
int goal=1;
//定义不同房间位置的坐标点
geometry_msgs::Pose startPoint;
geometry_msgs::Pose onePoint;
geometry_msgs::Pose twoPoint;
geometry_msgs::Pose OutPoint;

ros::Publisher nav2speech_pub;
ros::Subscriber move_sub;
ros::Subscriber speech_sub;
ros::Publisher nav_inspect;
bool switch_state=0;

void speechCallback(const std_msgs::String::ConstPtr& msg)
{
  /*if(msg->data == "go_out")
  {
	   step = 2;
	   cout<<"go_out"<<endl;
	}*/
if(msg->data == "false")
{
        ROS_INFO("switch_get");
	switch_state=true;
}
}


//主函数
int main(int argc, char** argv)
{
	//set pose
	//people
  startPoint.position.x =  7.59039;
  startPoint.position.y = -5.75835;
  startPoint.position.z = 0;
  startPoint.orientation.x = 0;
  startPoint.orientation.y = 0;
  startPoint.orientation.z = -0.682062;
  startPoint.orientation.w = 0.731294;
//2

  onePoint.position.x = 7.59039;
  onePoint.position.y = -5.75835;
  onePoint.position.z = 0;
  onePoint.orientation.x = 0;
  onePoint.orientation.y = 0;
  onePoint.orientation.z =  -0.682062;
  onePoint.orientation.w =  0.731294;

//3

  twoPoint.position.x = 8.00631;
  twoPoint.position.y = -5.97569;
  twoPoint.position.z = 0;
  twoPoint.orientation.x = 0;
  twoPoint.orientation.y = 0;
  twoPoint.orientation.z =  0.70532;
  twoPoint.orientation.w =  0.708889;

//4

  OutPoint.position.x = 10.2765;
  OutPoint.position.y = -7.89476;
  OutPoint.position.z = 0;
  OutPoint.orientation.x = 0;
  OutPoint.orientation.y = 0;
  OutPoint.orientation.z =  -0.022394;
  OutPoint.orientation.w =  0.999749;

	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	cout<<"Welcome to Help-me-carry!"<<endl;

	nav2speech_pub= myNode.advertise<std_msgs::String>("/nav2speech", 1);
	nav_inspect= myNode.advertise<std_msgs::String>("/inspect2speech", 1);

	//ros::Subscriber move_sub = myNode.subscribe("/doorstate", 1, moveCallback);
	ros::Subscriber speech_sub = myNode.subscribe("go_out", 1, speechCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
		ROS_INFO("INTO THE MAIN");
		if(switch_state==true)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			if(goal==1){
				naviGoal.target_pose.pose = geometry_msgs::Pose(onePoint);
				
			}
			if(goal==2){
				naviGoal.target_pose.pose = geometry_msgs::Pose(twoPoint);
				
			}
			if(goal==3){
				naviGoal.target_pose.pose = geometry_msgs::Pose(OutPoint);
				
			}

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
				nav_inspect.publish(str);
				goal++;
			}
		}
		ros::spinOnce();
	}
	return 0;
}
