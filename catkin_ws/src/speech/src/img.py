#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
    navigation.py - Say back what is heard by the pocketsphinx recognizer.
"""
import roslib; roslib.load_manifest('speech')
import rospy
import re
import os

from std_msgs.msg import String
from std_msgs.msg import Int8
import time
from sound_play.libsoundplay import SoundClient
class img:
	def __init__(self):
		rospy.on_shutdown(self.cleanup)
		self.voice = rospy.get_param("~voice", "voice_cmu_us_clb_arctic_clunits")
		self.soundhandle=SoundClient()
		rospy.sleep(2)
		self.loc_pub = rospy.Publisher('/voice2bring', String, queue_size=15)
		self.soundhandle.stopAll()
		self.soundhandle.say("ready",self.voice)
                rospy.Subscriber('/nav2speech',String, self.navcallback)
                rospy.Subscriber('say',String, self.img2speech)
	def navcallback(self,msg):
		msg.data=msg.data.lower()
		if msg.data=="arrived":
			self.soundhandle.say('i have arrived the position',self.voice) 
			os.system("/home/kamerider/catkin_ws/src/arm/raise_hand.sh")                      
  			rospy.sleep(4)
			self.soundhandle.say('i will take it back',self.voice)                       
  			rospy.sleep(2)
			os.system("/home/kamerider/catkin_ws/src/arm/grasp.sh")
			rospy.sleep(2)
		if msg.data=="release":
			self.soundhandle.say('dear bobo ',self.voice) 
  			rospy.sleep(1)
			self.soundhandle.say('i have taken it back',self.voice)                       
  			rospy.sleep(2)



	def img2speech(self,msg):
                print 1111111
                self.if_followme =0
		msg.data=msg.data.lower()
		print msg.data
		
                if self.if_followme ==0:
 
                        print msg.data
			if msg.data=='a': 
				self.soundhandle.say('is it edible',self.voice)
				rospy.sleep(10)
				
		if self.if_followme ==0:
 
			if msg.data=="b":
				self.soundhandle.say('Yes edible',self.voice)                       
  				rospy.sleep(3)
				
                if self.if_followme ==0:
 
                        
			if msg.data=="d":
				self.soundhandle.say('is it solid',self.voice)              
  				rospy.sleep(10)
                if self.if_followme ==0:
 
                        
			if msg.data=="f":
				self.soundhandle.say('No not solid',self.voice)              
  				rospy.sleep(3)
                if self.if_followme ==0:
 
                        
			if msg.data=="g":
				self.soundhandle.say('is it water',self.voice)              
				rospy.sleep(10)				
                if self.if_followme ==0:
 
                        
			if msg.data=="h":
				self.soundhandle.say('ok i will take the water for you',self.voice) 
				self.loc_pub.publish('littletable')             
  				rospy.sleep(2)
                
                if self.if_followme ==0:
 
                        
			if msg.data=="e":
				self.soundhandle.say('Yes solid',self.voice)              
  				rospy.sleep(3)
                if self.if_followme ==0:
 
                        
			if msg.data=="i":
				self.soundhandle.say('Is it apple',self.voice)              
  				rospy.sleep(10)
                if self.if_followme ==0:
 
                        
			if msg.data=="j":
				self.soundhandle.say('ok i will take an apple for you',self.voice)   
				self.loc_pub.publish('kitchentable')           
  				rospy.sleep(2)
                if self.if_followme ==0:
 
                        
			if msg.data=="c":
				self.soundhandle.say('No not edible',self.voice)              
  				rospy.sleep(3)
		if self.if_followme ==0:
 
                        
			if msg.data=="k":
				self.soundhandle.say('Is it electronic',self.voice)              
  				rospy.sleep(10)
		if self.if_followme ==0:
 
			if msg.data=="l":
				self.soundhandle.say('Yes it is electronic',self.voice)                       
  				rospy.sleep(3)
			
		if self.if_followme ==0:
 
			if msg.data=="n":
				self.soundhandle.say('is it television',self.voice)                       
  				rospy.sleep(10)

		if self.if_followme ==0:
 
			if msg.data=="o":
				self.soundhandle.say('ok i will turn on the TV',self.voice)    
				self.loc_pub.publish('diningroom')         
  				rospy.sleep(2)

		if self.if_followme ==0:
 
			if msg.data=="m":
				self.soundhandle.say('No it is not electronic',self.voice)                       
 				rospy.sleep(3)
              
		if self.if_followme ==0:
 
			if msg.data=="p":
				self.soundhandle.say('is it Glass',self.voice)                       
				rospy.sleep(10)

		if self.if_followme ==0:
 
			if msg.data=="q":
				self.soundhandle.say('ok i will take glass for you',self.voice)    
				self.loc_pub.publish('coffeetable')                   
				os.system("/home/kamerider/catkin_ws/src/arm/raise_hand.sh")
				rospy.sleep(3)

		if self.if_followme ==0:
 
			if msg.data=="r":
				self.soundhandle.say('my name is jack',self.voice)                       
				os.system("/home/kamerider/catkin_ws/src/arm/init.sh")
				rospy.sleep(4)
				
				self.soundhandle.say('can i help you ',self.voice)                       

				rospy.sleep(8)

	def cleanup(self):
		rospy.loginfo("shuting down navsp node ....")

if __name__=="__main__":
	rospy.init_node('img')
	try:
		img()
		rospy.spin()
	except:
		pass





