    #include <ros/ros.h>  
    #include <image_transport/image_transport.h>  
    #include <opencv2/highgui/highgui.hpp>  
    #include <cv_bridge/cv_bridge.h>  
    #include <sensor_msgs/image_encodings.h>
    #include <iostream>  
      
    using std::cout;
    using std::endl;  
    using std::stringstream;  
    using std::string;  
      
    unsigned int fileNum = 1;  
    bool saveCloud(false);  
      
    void imageCallback(const sensor_msgs::ImageConstPtr& msg)  
    {  
      cv::imshow("Show RgbImage", cv_bridge::toCvShare(msg,"rgb8")->image);  
      char key;  
      key=cvWaitKey(33);  
      if(key==32)           //the Ascii of "Space key" is 32   
      saveCloud = true;  
      if(saveCloud)  
      {  
        stringstream stream;  
        stringstream stream1;  
        stream <<"Goal RgbImage" << fileNum<<".jpg";  
        stream1 <<"/home/kamerider/catkin_ws/src/GetRgbImage/" << fileNum <<".jpg";  
        string filename = stream.str();  
        string filename1 = stream1.str();  
        cv::imwrite(filename1,cv_bridge::toCvShare(msg)->image);  
        saveCloud = false;  
        fileNum++;  
        cout << filename << " had Saved."<< endl;  
      }  
    }  
      
    int main(int argc, char **argv)  
    {  
      ros::init(argc, argv, "Image_listener");  
      ros::NodeHandle nh;  
      cv::namedWindow("Show RgbImage");  
      cv::startWindowThread();  
      image_transport::ImageTransport it(nh);  
      image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw", 1, imageCallback);  
      ros::spin();  
      cv::destroyWindow("Show RgbImage");  
    }  
