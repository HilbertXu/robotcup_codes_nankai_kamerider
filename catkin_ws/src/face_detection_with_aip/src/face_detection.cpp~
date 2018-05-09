#include <stdio.h>
#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <geometry_msgs/Twist.h>
//#include "/home/kamerider/catkin_ws/src/face_detection_with_aip/include/auto_tchar.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int static count1 = 0;

//订阅传感器话题获取图像
image_transport::Subscriber sub;

//订阅语音话题，准备转动机器人
ros::Subscriber sp_sub;
ros::Subscriber nav_sub;
//图像储存完成之后向PUBLISH_RET_TOPIC_NAME发布消息
ros::Publisher gPublisher;
ros::Publisher move_pub;
ros::Publisher taking_photo_Pub;

//TOPIC NAME
const std::string RECEIVE_IMG_TOPIC_NAME = "/camera/rgb/image_raw";
const std::string PUBLISH_RET_TOPIC_NAME = "/face_detected";
std_msgs::String photo_signal;
bool flag=false;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	if(flag == true)
	{
	  count1++;
	  ROS_INFO("IMAGE RECEIVED");
	  std_msgs::String info;
	  std::stringstream ss;
	  ss<<"Photo_Stored";
	  info.data = ss.str();
	  cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	  cv::Mat img = cv_ptr->image;
	  cv::imwrite("/home/kamerider/catkin_ws/src/face_detection_with_aip/face.jpg", img);
	  cv::namedWindow("Demo",CV_WINDOW_AUTOSIZE);
	  cv::imshow("Demo",img);
	  if(count1==10)
	  {
		cout<<count1;
		sub.shutdown();
		gPublisher.publish(info);
	  }
	}
}

void spCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("spCallback received: %s\n", msg->data.c_str());
    if(msg->data == "turn_robot")
    {
        cout<<"turn_signal_received\n";
        sleep(10);
        geometry_msgs::Twist vel;
        int count = 0;
        float time = 4.5;
        ros::Rate loop_rate(10);
        int num = time*10;
        //转180度
        float theta = 4.5;
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
        //pt.state = 0;
        //pt.time = time;
        //pt.vel = vel.angular.z;
        //vppt.push_back(pt);
        //vel.angular.z = 0.0;
        //move_pub.publish(vel);
        cout<<"转弯\n";
        sleep(2);
	photo_signal.data="start";
	taking_photo_Pub.publish(photo_signal);//向语音发布消息，提醒人们要拍照了
	sleep(5);
	
    }
}

void navCallback(const std_msgs::String::ConstPtr& msg)
{
	if(msg->data == "in_position")
		flag = true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "face_detection");
  ROS_INFO("--------INIT--------");
  //与语音导航的通信
  ros::NodeHandle nh;
  move_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",1);  //移动
  taking_photo_Pub = nh.advertise<std_msgs::String>("taking_photo_signal", 1);//即将拍照片的信号
  sp_sub = nh.subscribe("turn_signal", 1, spCallback);
  nav_sub = nh.subscribe("turn_end",1, navCallback);
  gPublisher = nh.advertise<std_msgs::String>(PUBLISH_RET_TOPIC_NAME, 1);

  
  //TO receive an image from the topic and save it
  image_transport::ImageTransport it(nh);
  sub = it.subscribe(RECEIVE_IMG_TOPIC_NAME, 1, imageCallback);
  
  ros::spin();
  ros::shutdown;
  return 0;
}
