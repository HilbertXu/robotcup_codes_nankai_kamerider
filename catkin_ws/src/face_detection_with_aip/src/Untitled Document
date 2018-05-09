#!/usr/bin/env python
# -*- coding: utf-8 -*-
import roslib
import rospy
from aip import AipFace
import cv2
import matplotlib.pyplot as plt
from std_msgs.msg import String
from std_msgs.msg import Int8
import os


class face_aip:
    def __init__(self):
        # 定义APP_ID、API_KEY、SECRET_KEY
        self.APP_ID = '11166463'
        self.API_KEY = 'UdIDb9h8Iq4OlNK1gWcbIYLg'
        self.SECRET_KEY = 'KeUbrad4RI9TlIWNwj8OcGFreyZQaHgz'
        self.filename = '/home/kamerider/catkin_ws/src/face_detection_with_aip/face.jpg'
        self.max_num = 10
        #发布器
	#self.move_pub = rospy.Publisher('cmd_vel_mux/input/navi',Twist,queue_size=1)
        self.male_pub = rospy.Publisher('male_num',String,queue_size=1)
	self.female_pub = rospy.Publisher('female_num',String,queue_size=1)
	self.human_pub = rospy.Publisher('human_num',String,queue_size=1)
	#self.take_photo_pub = rospy.Publisher('/taking_photo_signal',String,queue_size=1)
        #订阅器
        rospy.Subscriber('/face_detected',String,self.detection)

    #读取文件内容
    def get_file_content(self,filepath):
        with open(self.filename) as fp:
            return fp.read()

    #检测函数
    def detection(self,msg):
         msg.data=msg.data.lower()
         if msg.data == 'photo_stored':
            #读取原始图像
            img = cv2.imread(self.filename)
            cv2.imshow('source',img)
            #初始化aipfacce对象
            aipface = AipFace(self.APP_ID, self.API_KEY, self.SECRET_KEY)
            #设置
            options = {
            'max_face_num': 10,
            'face_fields':"gender",
            }
            #接收返回的检测结果
            result = aipface.detect(self.get_file_content(self.filename),options)
            #print result['result'][0]['gender']
            #print result['result_num']
            #初始化统计数据
            male_num=0
            female_num=0
            face_num = len(result['result'])
            #在原图像上标注人脸，并统计男性和女性的数目
            for i in range(face_num):
                location = result['result'][i]['location']
                left_top = (location['left'], location['top'])
                right_bottom = (left_top[0] + location['width'], left_top[1] + location['height'])
                if result['result'][i]['gender'] == 'male':
                    cv2.rectangle(img, left_top, right_bottom, (255, 0, 0), 2)
                if result['result'][i]['gender'] == 'female':
                    cv2.rectangle(img, left_top, right_bottom, (0, 0, 255), 2)
                if result['result'][i]['gender'] == 'male' :
                    male_num=male_num+1
                if result['result'][i]['gender'] == 'female' :
                    female_num = female_num + 1
            print male_num
            print female_num
            #向语音节点发布结果
            self.human_pub.publish(str(face_num))
            rospy.sleep(3)
            self.female_pub.publish(str(female_num))
            rospy.sleep(3)
            self.male_pub.publish(str(male_num))
            #保存并显示处理后的图片
            cv2.imwrite('/home/kamerider/catkin_ws/src/face_detection_with_aip/face_detected.jpg', img)
            cv2.imshow('result', img)
            cv2.waitKey(0)
            

	#def spCallback(self,msg)

if __name__ =='__main__':
    #初始化节点
    rospy.init_node('face_aip')
    print '----------init----------'
    print '-----WAITING FOR IMAGE-----'
    face_aip()
    rospy.spin()
