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
//#include "face_detection_with_aip/auto_tchar.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int static count1 = 0;
//bool static flags = false;
string static position;

//订阅传感器话题获取图像
image_transport::Subscriber sub;
//ros::Subscriber nav_sub;

//订阅语音话题，准备转动机器人
//ros::Subscriber sp_sub;
//图像储存完成之后向PUBLISH_RET_TOPIC_NAME发布消息
ros::Publisher gPublisher;


//TOPIC NAME
const std::string RECEIVE_IMG_TOPIC_NAME = "/camera/rgb/image_raw";
const std::string PUBLISH_RET_TOPIC_NAME = "/saving_groceries_photo";


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{

  count1++;
  ROS_INFO("IMAGE RECEIVED");
  std_msgs::String info;
  std::stringstream ss;
  ss<<"table_Photo_Saved";
  info.data = ss.str();
  cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  cv::Mat img = cv_ptr->image;
  cv::namedWindow("Demo",CV_WINDOW_AUTOSIZE);
  cv::imshow("Demo",img);
  if(count1==15)
  {
    cv::imwrite("/home/kamerider/catkin_ws/src/face_detection_with_aip/table_groceries.jpg", img);
    sub.shutdown();
    gPublisher.publish(info);
  }

}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "take_photo_store");
  ROS_INFO("--------INIT--------");
  //与导航的通信，到达指定地点后开始拍照
  ros::NodeHandle nh;
  //nav_sub = nh.subscribe("nav2img", 1, navCallback);
  gPublisher = nh.advertise<std_msgs::String>(PUBLISH_RET_TOPIC_NAME, 1);

  //TO receive an image from the topic and save it
  image_transport::ImageTransport it(nh);
  sub = it.subscribe(RECEIVE_IMG_TOPIC_NAME, 1, imageCallback);

  ros::spin();
  ros::shutdown;
  return 0;
}
