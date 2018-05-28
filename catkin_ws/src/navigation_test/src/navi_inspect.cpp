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

//定义不同房间位置的坐标点
geometry_msgs::Pose ViewPoint;
geometry_msgs::Pose OutPoint;

ros::Publisher nav2speech_pub;
ros::Subscriber move_sub;
ros::Subscriber speech_sub;
ros::Publisher nav_inspect;
bool switch_state=0;

void speechCallback(const std_msgs::String::ConstPtr& msg)
{
  if(msg->data == "go_out")
  {
	   step = 2;
	   cout<<"go_out"<<endl;
	}
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
ViewPoint.position.x =  12.8627;
  ViewPoint.position.y = 1.14987;
  ViewPoint.position.z = 0;
  ViewPoint.orientation.x = 0;
  ViewPoint.orientation.y = 0;
  ViewPoint.orientation.z = 0.662806;
  ViewPoint.orientation.w = 0.748791;
//2

  OutPoint.position.x = 8.57897;
  OutPoint.position.y = 3.25528;
  OutPoint.position.z = 0;
  OutPoint.orientation.x = 0;
  OutPoint.orientation.y = 0;
  OutPoint.orientation.z =  -0.0857846;
  OutPoint.orientation.w =  0.996314;

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
		if(step==0&&switch_state==true)
		{
			ROS_INFO("int to the circle");
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(ViewPoint);

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
			}

			step = 1;
		}
		if(step==2)
		{
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(OutPoint);

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
				cout<<"Yes! The robot has moved to another door!"<<endl;
			}
			step = 0;
		}
		ros::spinOnce();
	}
	return 0;
}
