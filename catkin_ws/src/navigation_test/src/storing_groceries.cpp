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
geometry_msgs::Pose TablePoint;
geometry_msgs::Pose OutPoint;

ros::Publisher nav2speech_pub;
ros::Subscriber move_sub;
ros::Subscriber speech_sub;
ros::Publisher nav_inspect;
bool switch_state=0;

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
	//set pose
	//people
	TablePoint.position.x = 2.88498;//0.860085680301;
	TablePoint.position.y = -0.0849408;//-2.83426480702;
	TablePoint.position.z = 0;
	TablePoint.orientation.x = 0;
	TablePoint.orientation.y = 0;
	TablePoint.orientation.z = 0.999744;//0.097098622328;
	TablePoint.orientation.w = 0.022604;//0.995274764847;

	ros::init(argc, argv, "navi_demo");
	ros::NodeHandle myNode;
	cout<<"Welcome to Help-me-carry!"<<endl;

	nav2speech_pub= myNode.advertise<std_msgs::String>("nav2speech", 1);
	nav_inspect= myNode.advertise<std_msgs::String>("inspect2speech", 1);

	//ros::Subscriber move_sub = myNode.subscribe("/doorstate", 1, moveCallback);
	ros::Subscriber speech_sub = myNode.subscribe("go_out", 1, speechCallback);

	MoveBaseClient  mc_("move_base", true); //建立导航客户端
	move_base_msgs::MoveBaseGoal naviGoal; //导航目标点
	while(ros::ok())
	{
		if(step==0&&switch_state==true)
		{
			naviGoal.target_pose.header.frame_id = "map";
			naviGoal.target_pose.header.stamp = ros::Time::now();
			naviGoal.target_pose.pose = geometry_msgs::Pose(TablePoint);

			while(!mc_.waitForServer(ros::Duration(5.0)))
			{
				//等待服务初始化
				cout<<"Waiting for the server..."<<endl;

			}
			mc_.sendGoal(naviGoal);
			mc_.waitForResult(ros::Duration(40.0));

			if(mc_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				cout<<"I have reach TablePoint"<<endl;
				std_msgs::String str;
				str.data = "get_pose";
				nav_inspect.publish(str);
			}

			step = 1;
		}
		ros::spinOnce();
	}
	return 0;
}
