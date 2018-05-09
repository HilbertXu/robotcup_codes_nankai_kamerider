#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <math.h>
//Includes all the headers necessary to use the most common public pieces of the ROS system.    
#include <ros/ros.h>
#include <string>        
#include <sstream> 
#include <vector>  
#include <list>  
#include <map>  
#include <stack> 
#include <iostream>  
#include <stdio.h>
#include<algorithm>
#include <geometry_msgs/Twist.h>   
#include <sensor_msgs/PointCloud2.h>  
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <opencv2/core/core.hpp>      
//Use image_transport for publishing and subscribing to images in ROS    
#include <image_transport/image_transport.h>    
//Use cv_bridge to convert between ROS and OpenCV Image formats    
#include <cv_bridge/cv_bridge.h>    
#include <sensor_msgs/image_encodings.h>    
//Include headers for OpenCV Image processing    
#include <opencv2/imgproc/imgproc.hpp>    
//Include headers for OpenCV GUI handling    
#include <opencv2/highgui/highgui.hpp>    
#include "opencv2/objdetect/objdetect.hpp"  
#include <opencv2/core/core.hpp>   
#include <opencv2/features2d/features2d.hpp>  
#include <opencv2/calib3d/calib3d.hpp> 
#include <std_msgs/String.h> 
#include "/home/kamerider/catkin_ws/src/imgpcl/include/imgpcl/auto_tchar.h"
// time synchronize
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <ros/callback_queue.h>
#include <boost/bind.hpp>
#include <geometry_msgs/Point.h>
#include <time.h>
//#include "/home/kamerider/emergency_stop/src/my_estop/include/imgpcl/objectDetect.hpp"
using namespace cv;
using namespace std;
//Store all constants for image encodings in the enc namespace to be used later.      
namespace enc = sensor_msgs::image_encodings;
namespace enc = sensor_msgs::image_encodings; 

typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::PointCloud2> MySyncPolicy;

void forward_robot(float x,float time);
void turn_robot(float theta,float time);      
      
string detect_begin = "";

static int imgWidth, imgHeight;
ros::Publisher move_pub; //向navigation发消息，微调机器人
ros::Publisher image2voice_Pub;
ros::Publisher notice_Pub;
ros::Publisher image2nav_Pub;
ros::Publisher image2navi_Pub;
void detectAndDisplay(Mat frame); 
/// 全局变量
String face_cascade_name = "/home/kamerider/catkin_ws/src/imgpcl/haarcascade_frontalface_alt.xml"; 
//String eyes_cascade_name = "/home/kamerider/catkin_ws/src/imgpcl/haarcascade_eye_tree_eyeglasses.xml";  
CascadeClassifier face_cascade;  
//int turnnum = 1;//turn robot times
//CascadeClassifier eyes_cascade;  
int turn_num=0;
int notfind_num=0;
int find_num=0;
int step = -1;
             
double bSums(Mat src)  
{  
      
    int white_pixel = 0;
    int max_pixel = 0;
    double counter =0;
    //迭代器访问像素点
    threshold(src,src,200,255,THRESH_BINARY);//二值化   
    Mat_<uchar>::iterator it = src.begin<uchar>();  
    Mat_<uchar>::iterator itend = src.end<uchar>();    
    for (; it!=itend; ++it)  
    {  
        if((*it)>0) white_pixel+=1;//二值化后，像素点是0或者255
        max_pixel+=1; 
    }
    counter=double(white_pixel)/double(max_pixel);
    cout<<white_pixel<<"   "<<max_pixel<<"  "<<counter<<endl;
    return counter;  
}    
class WatershedSegmenter 
{  
    private:  
        cv::Mat markers;  
    public:  
        void setMarkers(const cv::Mat& markerImage)
        {  
            // Convert to image of ints  
            markerImage.convertTo(markers, CV_32S);  
        }  
        cv::Mat process(const cv::Mat &image)
        {  
      
            // Apply watershed  
            cv::watershed(image, markers);  
            return markers;  
        }  
        // Return result in the form of an image  
        cv::Mat getSegmentation()
        {  
      
            cv::Mat tmp;  
            // all segment with label higher than 255  
            // will be assigned value 255  
            markers.convertTo(tmp, CV_8U);  
            return tmp;  
        }  
      
        // Return watershed in the form of an image  
        cv::Mat getWatersheds()
        {  
            cv::Mat tmp;  
            markers.convertTo(tmp, CV_8U,255, 255);  
            return tmp;  
        }  
};  
void Seed_Filling(const cv::Mat& binImg, cv::Mat& labelImg, int& labelNum, int (&ymin)[20], int(&ymax)[20], int(&xmin)[20], int(&xmax)[20])   //种子填充法
{  
    if (binImg.empty() || binImg.type() != CV_8UC1)
    {  
        return;
    }  
  
    labelImg.release();  
    binImg.convertTo(labelImg, CV_32SC1);  
    int label = 1;  
    int rows = binImg.rows - 1;  
    int cols = binImg.cols - 1;  
    for (int i = 1; i < rows - 1; i++)  
    {  
        int* data = labelImg.ptr<int>(i);  
        for (int j = 1; j < cols - 1; j++)  
        {  
            if (data[j] == 1)  
            {  
                std::stack<std::pair<int, int> > neighborPixels;  
                neighborPixels.push(std::pair<int, int>(j, i));     // 像素位置: <j,i>    
                ++label;  // 没有重复的团，开始新的标签   
                ymin[label] = i;  
                ymax[label] = i;  
                xmin[label] = j;  
                xmax[label] = j;  
                while (!neighborPixels.empty())  
                {  
                    std::pair<int, int> curPixel = neighborPixels.top(); //如果与上一行中一个团有重合区域，则将上一行的那个团的标号赋给它    
                    int curX = curPixel.first;  
                    int curY = curPixel.second;  
                    labelImg.at<int>(curY,curX) = label;  
  
                    neighborPixels.pop();  
  
                    if ((curX>0)&&(curY>0)&&(curX<(cols-1))&&(curY<(rows-1)))  
                    {   
                        if (labelImg.at<int>(curY - 1,curX) == 1)                     //上  
                        {  
                            neighborPixels.push(std::pair<int, int>(curX, curY - 1));  
                            //ymin[label] = curY - 1;  
                        }  
                        if (labelImg.at<int>( curY + 1,curX) == 1)                        //下  
                        {  
                            neighborPixels.push(std::pair<int, int>(curX, curY + 1));  
                            if ((curY+1)>ymax[label])  
                                ymax[label] = curY + 1;  
                        }  
                        if (labelImg.at<int>(curY,curX - 1) == 1)                     //左  
                        {  
                            neighborPixels.push(std::pair<int, int>(curX - 1, curY));  
                            if ((curX - 1)<xmin[label])  
                                xmin[label] = curX - 1;  
                        }  
                        if (labelImg.at<int>(curY,curX + 1) == 1)                     //右  
                        {  
                            neighborPixels.push(std::pair<int, int>(curX + 1, curY));  
                            if ((curX + 1)>xmax[label])  
                                xmax[label] = curX + 1;  
                        }  
                        if (labelImg.at<int>(curY - 1,curX-1) == 1)                   //左上  
                        {    
                            neighborPixels.push(std::pair<int, int>(curX - 1, curY - 1));  
                            //ymin[label] = curY - 1;  
                            if ((curX - 1)<xmin[label])  
                                xmin[label] = curX - 1;  
                        }  
                        if (labelImg.at<int>(curY + 1,curX+1) == 1)                   //右下  
                        {    
                            neighborPixels.push(std::pair<int, int>(curX+1, curY + 1));  
                            if ((curY + 1)>ymax[label])  
                                ymax[label] = curY + 1;  
                            if ((curX + 1)>xmax[label])  
                                xmax[label] = curX + 1;  
  
                        }  
                        if (labelImg.at<int>( curY + 1,curX - 1) == 1)                    //左下  
                        {   
                            neighborPixels.push(std::pair<int, int>(curX - 1, curY+1));  
                            if ((curY + 1)>ymax[label])  
                                ymax[label] = curY + 1;  
                            if ((curX - 1)<xmin[label])  
                                xmin[label] = curX - 1;  
                        }  
                        if (labelImg.at<int>( curY - 1,curX + 1) == 1)                    //右上  
                        {  
                            neighborPixels.push(std::pair<int, int>(curX + 1, curY-1));  
                            //ymin[label] = curY - 1;  
                            if ((curX + 1)>xmax[label])  
                                xmax[label] = curX + 1;  
  
                        }  
                    }  
                }  
            }  
        }  
    }  
    labelNum = label-1;  
}
void turn_robot(float theta,float time)
{
    geometry_msgs::Twist vel;
    int count = 0;

    ros::Rate loop_rate(10);
    int num = time*10;
	float theta2 = theta/time;
	vel.angular.z = theta2;
	/*if(abs(theta)<0.1)
		vel.angular.z =0;
	else
	{
		
		if(theta2 > 0)
		{
			vel.angular.z = (theta2 > 0.8)?0.8:theta2;    
		}
		else
		{
			vel.angular.z = (theta2 > -0.8)?theta2:-0.8;
		}
	//theta = ( ((320 - x)/320.0*1.5) > 0.5 )?0.5:((320 - x)/320.0*1.5);
	// vel.angular.z = theta; 
	}*/
    count = 0;
    while(count < num)
    {
        count++;
        move_pub.publish(vel);
        loop_rate.sleep();
    }
    vel.angular.z = 0.0;
    move_pub.publish(vel);
    sleep(1.6);
}
void forward_robot(float x,float time)
{
    geometry_msgs::Twist vel;
    int count = 0;
    
    vel.linear.x = x/time;

	/*if(vel.linear.x > 0.05)
		vel.linear.x = 0.05;
	else if(vel.linear.x < 0.02)
		vel.linear.x = 0.02;*/

    ros::Rate loop_rate(10);
    int num = time*10;
    //cout<<"armCallback1()\n";
    while(count < num)
    {
        count++;
        move_pub.publish(vel);
        loop_rate.sleep();
    }
    vel.linear.x = 0.0;
    move_pub.publish(vel);
    cout<<"直行\n";
    sleep(1);
} 
float detectHand( Mat& frame )  
{   
	Mat binImage,tmp;  
	Mat Y, Cr, Cb;   
	cvtColor(frame, binImage, CV_BGR2GRAY); 
	 
	//frame.copyTo(tmp);  
	cvtColor(frame, tmp, CV_BGR2YCrCb);  
	vector<Mat> channels(tmp.channels());
	split(tmp, channels);  

	Cr = channels[1];  
	Cb = channels[2];  
    //肤色检测，输出二值图像  
    for (int j = 1; j < Cr.rows - 1; j++)  
    {  
        uchar* currentCr = Cr.ptr< uchar>(j);  
        uchar* currentCb = Cb.ptr< uchar>(j);  
        uchar* current = binImage.ptr< uchar>(j);  
        for (int i = 1; i < Cb.cols - 1; i++)  
        {
            if ((currentCr[i] > 140) && (currentCr[i] < 170)  &&(currentCb[i] > 77) && (currentCb[i] < 123))  
                current[i] = 255;  
            else  
                current[i] = 0;  
        }  
    }  
    //形态学处理  
    dilate(binImage, binImage, Mat());  
    //分水岭算法  
    cv::Mat fg;  
    cv::erode(binImage, fg, cv::Mat(), cv::Point(-1, -1), 6);  
    // Identify image pixels without objects  
    cv::Mat bg;  
    cv::dilate(binImage, bg, cv::Mat(), cv::Point(-1, -1), 6);  
    cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);  
    // Show markers image  

    cv::Mat markers(binImage.size(), CV_8U, cv::Scalar(0));  
    markers = fg + bg;  
    // Create watershed segmentation object  

    WatershedSegmenter segmenter; 
    segmenter.setMarkers(markers);
    if(frame.empty())return 0;
    segmenter.process(frame);
    Mat waterShed;  
    waterShed = segmenter.getWatersheds();  
    //imshow("watershed", waterShed);  
    //获得区域边框  
    threshold(waterShed, waterShed, 1, 1, THRESH_BINARY_INV);  

    //8向种子算法，给边框做标记  
    Mat labelImg;  
    int label, ymin[20], ymax[20], xmin[20], xmax[20];  
    Seed_Filling(waterShed, labelImg, label, ymin, ymax, xmin, xmax);  
    //统计一下区域中的肤色区域比例  
    float fuseratio[20];  
    for (int k = 0; k < label; k++)  
    {  
        fuseratio[k] = 1;  
        if (((xmax[2 + k] - xmin[2 + k])>50) && ((ymax[2 + k] - ymin[2 + k]) > 50))  
        {  
            int fusepoint=0;  
            for (int j = ymin[2+k]; j < ymax[2+k]; j++)  
            {  
                uchar* current = binImage.ptr< uchar>(j);  
                for (int i = xmin[2+k]; i < xmax[2+k]; i++)  
                {  
                    if (current[i] == 255)  
                        fusepoint += 1;  
                }  
            }  
            fuseratio[k] = float(fusepoint) / ((xmax[2 + k] - xmin[2 + k])*(ymax[2 + k] - ymin[2 + k]));  
            //cout << fuseratio[k] << endl;  
        }  
    }
    //imshow("frame", frame);  
    Mat element5(5,5,CV_8U,cv::Scalar(1));

    //////////////////////////////////////////////////////////////////////////////////////change for better performer
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode( binImage,binImage,element); //腐蚀
    medianBlur(binImage, binImage, 5);  
    dilate( binImage,binImage,element); //膨胀
    dilate( binImage,binImage,element); 
    float diff=0;
    diff=bSums(binImage);
    cout<<diff<<endl;
    imshow("test", binImage);  
    waitKey(10);
    cout<<"detectHand OVER"<<endl;
    return diff;
}

bool faceRec(Mat frame, Rect &faceRect)
{
	//cout<<"faceRec()"<<endl;
	if( frame.empty() )
	{
		ROS_INFO("Camera image empty");
		return false;//break;
	}
	imshow("image", frame);//显示图片
	waitKey(10);
	bool return_value = false;
	if(detect_begin=="wave")
	{
		
		if( !face_cascade.load( face_cascade_name ) )
		{
			printf("--(!)Error loading\n");
		};
		//forward_robot(0.4);
			////检测人脸
		std::vector<Rect> faces;  
		Mat frame_gray;  
		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		equalizeHist( frame_gray, frame_gray ); 
		face_cascade.detectMultiScale( frame_gray, faces, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );  
		for( size_t i = 0; i < faces.size(); i++ )  
		{
			ROS_INFO("--------!!!!!!!---------"); 
			CvPoint P1,P2;
			CvPoint P3,P4;

			P1.x=P1.y=P2.x=P2.y=P3.x=P3.y=P4.x=P4.y=0;
			P1.x=faces[i].x- faces[i].width- faces[i].width;  
			P1.y=faces[i].y-faces[i].height;  
			P2.x=P1.x+ faces[i].width+ faces[i].width*2/3;
			P2.y= faces[i].y + faces[i].height+ faces[i].height;
			if(P1.x<0) 
				P1.x=0;
			if(P1.x>imgWidth) 
				P1.x=imgWidth;
			if(P1.y<0) 
				P1.y=0;
			if(P1.y>imgHeight) 
				P1.y=imgHeight;
			if(P2.x<0) 
				P2.x=0;
			if(P2.x>imgWidth) 
				P2.x=imgWidth;
			if(P2.y<0) 
				P2.y=0;
			if(P2.y>imgHeight) 
				P2.y=imgHeight;

			P3.x=faces[i].x+ faces[i].width+ faces[i].width*2/3;  
			P3.y=faces[i].y-faces[i].height;  
			P4.x=P3.x+ faces[i].width+ faces[i].width;
			P4.y= faces[i].y + faces[i].height+ faces[i].height;
			if(P3.x<0) 
				P3.x=0;
			if(P3.x>imgWidth) 
				P3.x=imgWidth;
			if(P3.y<0) 
				P3.y=0;
			if(P3.y>imgHeight) 
				P3.y=imgHeight;
			if(P4.x<0) 
				P4.x=0;
			if(P4.x>imgWidth) 
				P4.x=imgWidth;
			if(P4.y<0) 
				P4.y=0;
			if(P4.y>imgHeight) 
				P4.y=imgHeight;
			Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 ); 
			rectangle( frame,faces[i].tl(), faces[i].br(), (0,0,255), 2, 8, 0 );
			rectangle(frame,P1 ,P2,(0, 255, 0), 2,8,0);
			rectangle(frame,P3 ,P4,(0, 255, 0), 2,8,0); 
			Mat wave_area1,wave_area2; 
			wave_area1=frame(Rect(P1.x,P1.y,P2.x-P1.x,P2.y-P1.y));
			wave_area2=frame(Rect(P3.x,P3.y,P4.x-P3.x,P4.y-P3.y));
			ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );  
			// imshow("wave1",wave_area1);
			// imshow("wave2",wave_area2);
			//检测挥手
			float diff1 = detectHand(wave_area1);
			float diff2 = detectHand(wave_area2);
			if(diff1>0.11 || diff2>0.11)
			{
				if((faces[i].x+faces[i].width*0.5) -320 > 80)
            		turn_robot(-0.2,0.5);
        		
        		if((faces[i].x+faces[i].width*0.5) - 320 < -80)
            		turn_robot(0.2,0.5);
            	
            	if(((faces[i].x+faces[i].width*0.5) - 320 <= 80)&&((faces[i].x+faces[i].width*0.5) - 320 >= -80))
            	{
					faceRect = faces[i];
					return_value = true;
				}
			}
			cout<<"faces[i].size : "<<faces[i].width*faces[i].height<<endl; 
		}
		imshow("face",frame);
		stringstream sss;        
		string strs;      
		strs="/home/kamerider/catkin_ws/src/imgpcl/wave_person";    
		sss.clear();        
		sss<<strs;              
		sss<<".jpg";        
		sss>>strs;
	    imwrite(strs,frame);//保存图片   
		waitKey(10);
		cout<<"faceRec()OVER"<<endl;
	}

	return return_value;
}

bool isShorter(const pcl::PointXYZ s1 , const pcl::PointXYZ s2)
{
	return s1.z<s2.z;
}

//由二维图像坐标到三维点云坐标的转换
bool rect_2Dto3D(const pcl::PointCloud<pcl::PointXYZ> & Points, CvRect rc, geometry_msgs::Point & p)
{
	vector<pcl::PointXYZ> vpt;     //储存所有可能的点
	for(int i=rc.x; i<rc.x+rc.width; i++)
	{
	    for(int j=rc.y; j<rc.y+rc.height; j++)
	    {
            //if( !(isnan(Points(j,i).x) || isnan(Points(j,i).y) || isnan(Points(j,i).z)) )
            //{
                pcl::PointXYZ pt;
                pt.x = Points(j,i).x;
                pt.y = Points(j,i).y;
                pt.z = Points(j,i).z;
                vpt.push_back(pt);
            //}
	    }
	}
	cout<<vpt.size()<<endl;
	if(vpt.size() < 2)
		return false;
	else
	{
		sort(vpt.begin(),vpt.end(),isShorter);
		p.x = vpt[0].z;
		p.y = vpt[0].x;
		p.z = 0;
		cout<<"position: x:"<<p.x<<" y:"<<p.y<<"--------------------"<<endl; 
		cout<<"finish"<<endl;
		return true;
	}
	
}

//This function is called everytime a new image is published    
void callback(const sensor_msgs::ImageConstPtr& image, const sensor_msgs::PointCloud2::ConstPtr& Callback_Points)
{

	if((detect_begin == "stop")||(step == -1))
	{
		return;
	}
	else
	{
		//---------------获取彩色图像------------------//
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}

		Mat imgColor = cv_ptr->image;

		//---------------获得点云数据------------------//
		pcl::PointCloud<pcl::PointXYZ> points_xyz;
		pcl::fromROSMsg (*Callback_Points, points_xyz);
	   
		Rect faceRect;
		geometry_msgs::Point facep;
		bool is_find = false;
		
		is_find = faceRec(imgColor , faceRect);
		cout<<"isfind:"<<is_find<<endl;
		
   	   
   	    //二维坐标转换为三维坐标，p为物体关于摄像头的坐标
   	   if(step == 1)
   	   {
			if(is_find)
			{
				notfind_num=0;
				turn_num=0;
				find_num++;
	   	   		bool is_3dP=rect_2Dto3D(points_xyz, faceRect, facep);
		   	   if(!is_3dP)//发布facep即为人脸相对于摄像头的3D位置
		   	   {
				   ROS_INFO("NO PCL!!\n");
			   }
		   	   else
		   	   {
					cout<<"find_num======"<<find_num<<endl;
		   	   		if(find_num>=2)
		   	   		{
			   	   		//cout<<"//////////////"<<endl;
			   	   		if((!isnan(facep.x))&&(!isnan(facep.y)))
			   	   		{
			   	   			std_msgs::String str;
			   	   			str.data = "notice";
			   	   			notice_Pub.publish(str);
			   	   			image2nav_Pub.publish(facep);
			   	   			detect_begin = "stop";
			   	   		}
		   	   		}
				}
			}
			else
			{
				find_num=0;
				notfind_num++;
				if(notfind_num%2==0)
				{
					if(turn_num<3||turn_num>=9&&turn_num<12)
						turn_robot(-0.5,1);
					if(turn_num>=3&&turn_num<9)
						turn_robot(0.5,1);
			   	    if(turn_num== 12)
			   	    {
			   	    	std_msgs::String str;
			   	    	str.data = "nextviewpoint";
			   	    	image2navi_Pub.publish(str);
			   	    	notfind_num=0;
			   	    	turn_num=0;
			   	    }
					turn_num++;
				}
			}
		}
		if(step == 2)
		{
			if(is_find)
			{
				notfind_num=0;
				if(faceRect.width*faceRect.height < 6200)
					forward_robot(0.2,1);
				else
				{
					std_msgs::String str;
					str.data = "reached_person";
					image2voice_Pub.publish(str);
  					cout<<"waveInfoCallback  face place x:"<<facep.x<<" place y:"<<facep.y<<endl;
					step = -1;
				}
			}
			else
			{
				//find_num=0;
				notfind_num++;
				if(notfind_num%2==0)
				{
					//if(turn_num<12)
					turn_robot(-0.9,1);
			   	    /*if(turn_num== 12)
			   	    {
			   	    	std_msgs::String str;
			   	    	str.data = "nextviewpoint";
			   	    	image2navi_Pub.publish(str);
			   	    	//cout<<"turn55555555555555"<<endl;
			   	    	notfind_num=0;
			   	    	turn_num=0;
			   	    }*/
					turn_num++;
				}
			}
		}
	}
}
        
/** 
* This is ROS node to track the destination image 
*/    
void navCallback(const std_msgs::String& msg)
{
	if(msg.data == "wave")
	{
		//forward_robot(3,9);
                forward_robot(1,4);
		sleep(4);
		detect_begin = "wave";
		step = 2;
		cout<<"navInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
	if(msg.data == "wavenewplace")
	{
		detect_begin = "wave";
		step = 1;
		cout<<"navInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
	if(msg.data == "stopvel")
	{
		detect_begin = "stop";
		cout<<"waveInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
}
void waveInfoCallback(const std_msgs::String::ConstPtr& msg)    
{
  //Store the image width for calculation of angle    
  	if(msg->data == "wave")
	{
		detect_begin = "wave";
		step = 1;
  		cout<<"waveInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
	
	if(msg->data == "stop")
	{
		detect_begin = "stop";
		step = -1;
		turn_num=0;
		notfind_num=0;
		find_num=0;
		cout<<"waveInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
	if(msg->data == "stopvel")
	{
		detect_begin = "stop";
		cout<<"waveInfoCallback  "<<"detect_begin:"<<detect_begin<<" step:"<<step<<endl;
	}
}
//This function is called everytime a new image_info message is published    
void camInfoCallback(const sensor_msgs::CameraInfo & camInfoMsg)    
{    
  //Store the image width for calculation of angle    
  imgWidth = camInfoMsg.width;    
  imgHeight = camInfoMsg.height;    
}
int main(int argc, char **argv)    
{    
    ros::init(argc, argv, "restaurant_wave");    
    ROS_INFO("-----------------");    
    ros::NodeHandle nh;    
    image_transport::ImageTransport it(nh);    
    ros::Subscriber camInfo         = nh.subscribe("/kinect/rgb/camera_info", 1, camInfoCallback);
    ros::Subscriber waveInfo_sub     = nh.subscribe("/detectWave", 1, waveInfoCallback);
    ros::Subscriber nav_sub     = nh.subscribe("/speech2nav", 1, navCallback);
        //话题的同步性，image_raw, depth/image, depth/points
    int global_subscriber_queue_size = 1;
    message_filters::Subscriber<sensor_msgs::Image> visual_sub_ (nh, "/kinect/rgb/image_raw", global_subscriber_queue_size);
    message_filters::Subscriber<sensor_msgs::PointCloud2> cloud_sub_(nh, "/kinect/depth/points", global_subscriber_queue_size);   
    message_filters::Synchronizer<MySyncPolicy> sync_(MySyncPolicy(1),  visual_sub_, cloud_sub_);
    sync_.registerCallback(boost::bind(&callback, _1, _2));

    move_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",1);  //移动        
    image2voice_Pub = nh.advertise<std_msgs::String>("/img2voice", 1);
    image2nav_Pub = nh.advertise<geometry_msgs::Point>("/img2nav", 1);
    notice_Pub = nh.advertise<std_msgs::String>("/notice_person", 1);
    image2navi_Pub = nh.advertise<std_msgs::String>("/img2navi", 1);

    //ROS_INFO is the replacement for printf/cout.    
    ROS_INFO("tutorialROSOpenCV::main.cpp::No error.");  
    ros::spin();
    return 0;  
}
