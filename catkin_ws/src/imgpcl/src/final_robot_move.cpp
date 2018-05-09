
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
//#include <object/pos.h>
#include <std_msgs/Int32.h> 
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

#include <nav_msgs/Odometry.h>



using namespace std;

#define PI 3.1415926
struct PathPoint
{
	int state;
	float vel;
	float time;
};
//void print(BTnode *t)
//{
//	if (t != NULL)
//	{
//		cout << t->ch;
//		print(t->left);
//		print(t->right);
//	}
//}

vector<PathPoint> vppt;             //储存反馈调节时的调节参数

ros::Publisher  move_pub;
ros::Publisher voice_pub;
std_msgs::String say;
void turn_robot(float theta,float time)
{
	geometry_msgs::Twist vel;
	int count = 0;
	//float time = 2;
	ros::Rate loop_rate(10);
	int num = time*10;
	PathPoint pt;
	//转90度
	//float theta = 5;
	//cout<<"theta:"<<theta<<endl;
	float theta2 = theta/time;
	vel.angular.z = theta2;    
	count = 0;
	num = time*10;
	while(count < num)
	{
		count++;
		move_pub.publish(vel);
		loop_rate.sleep();
	}
	pt.state = 0;
	pt.time = time;
	pt.vel = vel.angular.z;
	vppt.push_back(pt);
	vel.angular.z = 0.0;
	move_pub.publish(vel);
	cout<<"转弯\n";
	sleep(1);
}
void forward_robot(float x, float time)
{
	geometry_msgs::Twist vel;
	int count = 0;
	//float time = 4;
	vel.linear.x = x/time; 
	ros::Rate loop_rate(10);
	int num = time*10;
	//cout<<"armCallback1()\n";
	while(count < num)
	{
		count++;
		move_pub.publish(vel);
		loop_rate.sleep();
	}
	PathPoint pt;
	pt.state = 0;
	pt.time = time;
	pt.vel = vel.linear.x;
	vppt.push_back(pt);
	vel.linear.x = 0.0;
	move_pub.publish(vel);
	cout<<"直行\n";
	sleep(1);
}
void ssvepCallback(const std_msgs::String::ConstPtr& msg);
int main(int argc, char **argv) 
{   	
        
	ros::init(argc, argv, "robot_move");
	ros::NodeHandle nh_;
	voice_pub = nh_.advertise<std_msgs::String>("say", 1);
	//navigation_pub =s nh_.advertise<std_msgs::String>("/navigation/output", 1);
	ros::Subscriber move_sub = nh_.subscribe("socket2topic_nd",1000, ssvepCallback);        //订阅arm的消息
	move_pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",1);  //移动mobile_base/commands/velocity
	ros::spin();

	return 0;
}


void ssvepCallback(const std_msgs::String::ConstPtr& msg)
{   
	char cmd = 0;
	string value = msg->data;
	cmd = value[0];
	//////////////
        say.data=cmd;
        voice_pub.publish(say);


	//    
	//  //cout << "cmd = " << cmd <<"\tangle = " << angle << endl;   
	//  switch(cmd)
	//  {
	//      case 'f':    
	//          cout<<"\tforward\n";
	//          say.data = "forward";
	//          voice_pub.publish(say); 
	//          forward_robot(0.4,3);
	//          break;
	//      case 'b':
	//          cout<<"\tbackward\n";
	//          say.data = "backward";
	//          voice_pub.publish(say); 
	//          forward_robot(-0.4,3);
	//          break;
	//      case 'l':  
	//          cout<<"\tturn left\n";             
	//          say.data = "turn left";
	//          voice_pub.publish(say); 
	//          turn_robot(2.6,2);
	//          break;
	//      case 'r':
	//          cout<<"\tturn right\n";
	//          say.data = "turn right";
	//          voice_pub.publish(say); 
	//          turn_robot(-2.6,2);
	//          break;
	//      case 's':
	//	cout<<"\tstop\n";
	//	forward_robot(0,1);
	//default:
	//    break;
	//  }
	//  //move_pub.publish(vel);

}
